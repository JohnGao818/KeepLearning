面对大流量的用户访问，几乎所有的公司都会采用负载均衡的方式来分担访问压力。在负载均衡的场景下，服务端通常被部署为多个。用户的访问请求通过负载均衡策略被调度到其中一个服务端。在某些特定的情形下，你可能需要在副本间同步一个请求或消息。通常的做法是，其中一个副本将已知的消息发送到消息队列或者redis缓存数据库，其他副本对该消息进行消费。jgroups是另外一个不错的选择，它使副本可以直接互相通信，省去了中间件的依赖。在传统的虚机部署服务的场景下，你需要在每个副本中配置其他所有副本的ip地址，jgroups会逐一向其他副本尝试进行通信，通信成功的副本被加入到一个组中，组中的每个副本都可以在组内进行消息的广播。
## 在kubernetes中运行JGroups
> 这是一篇有关如何在kubernetes中使用JGroups的简短教程。我向大家分享了一个maven依赖包，它可以允许JGroups通过kubernetes的API来发现JGroup成员。因此，它还需要使用serviceAccounts通过指定的命名空间或标签亦或两者的组合去向kubernetes API请求可用的pod。如果你使用了RBAC,你还必须先定义一个拥有pod的查询权限的角色。
#### 创建一个简单的应用
这是一个创建UUID并通过JGroups将它发送给网络内的其他成员的小型应用程序。首先，我们需要添加maven依赖:
```xml
<dependency>
      <groupId>org.jgroups.kubernetes</groupId>
      <artifactId>jgroups-kubernetes</artifactId>
      <version>1.0.3.Final</version>
  </dependency>
```
这个依赖包是开箱即用的，它已经包含了jgroups依赖项，所以我们就不需要再添加jgroups了。
然后我们编写java代码用以发送和接收消息：
```java
@SpringBootApplication
@EnableScheduling
public class JgroupsApplication implements CommandLineRunner {

  private final Logger logger = LoggerFactory.getLogger(this.getClass());
  private JChannel channel;

  public static void main(String[] args) {
    SpringApplication.run(JgroupsApplication.class, args);
  }


  @Override
  public void run(String... args) throws Exception {
    InputStream resource = getClass().getResourceAsStream("/config.xml");
    this.channel = new JChannel(resource);
    channel.setReceiver(new ReceiverAdapterImpl());
    channel.connect("ChatCluster");
  }

  @Scheduled(fixedRate = 5000)
  public void sendMessage() throws Exception {
    String message = UUID.randomUUID().toString();
    logger.info("Send message '{}'", message);
    Message msg = new Message(null, message);
    channel.send(msg);
  }
}
```
```java
public class ReceiverAdapterImpl extends ReceiverAdapter {

    @Override
    public void receive(Message msg) {
        System.out.println("received message from: " + msg.getSrc() + " with content: " + msg.getObject());
    }
}
```
如上所示，我们启动了一个定时任务每5s发送一条消息并且记录在日志中。然后我们继承了类ReceiverAdapter并且重写了receive方法。在这里我们同样也记录了日志。
接下来我们需要定义config.xml文件，在这里我们指定了KUBE_PING协议并且设置了命名空间和标签：
```xml
<!--
  TCP-based configuration for running on Kubernetes
  Author: Bela Ban
-->

<config xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xmlns="urn:org:jgroups"
        xsi:schemaLocation="urn:org:jgroups http://www.jgroups.org/schema/jgroups.xsd">
    <TCP
            external_addr="${JGROUPS_EXTERNAL_ADDR:match-interface:eth0}"
            bind_addr="site_local,match-interface:eth0"
            bind_port="${TCP_PORT:7800}"

            recv_buf_size="5M"
            send_buf_size="1M"
            max_bundle_size="64K"
            enable_diagnostics="true"
            thread_naming_pattern="cl"

            thread_pool.min_threads="0"
            thread_pool.max_threads="500"
            thread_pool.keep_alive_time="30000" />

    <org.jgroups.protocols.kubernetes.KUBE_PING
        port_range="1"
        namespace="${KUBE_NAMESPACE:jgroups-example}"
    />

    <MERGE3 max_interval="30000"
            min_interval="10000"/>
    <FD_SOCK external_addr="${JGROUPS_EXTERNAL_ADDR}"
             start_port="${FD_SOCK_PORT:9000}"/>
    <FD_ALL timeout="30000" interval="5000"/>
    <VERIFY_SUSPECT timeout="1500"  />
    <BARRIER />
    <pbcast.NAKACK2 xmit_interval="500"
                    xmit_table_num_rows="100"
                    xmit_table_msgs_per_row="2000"
                    xmit_table_max_compaction_time="30000"
                    use_mcast_xmit="false"
                    discard_delivered_msgs="true" />
    <UNICAST3
            xmit_table_num_rows="100"
            xmit_table_msgs_per_row="1000"
            xmit_table_max_compaction_time="30000"/>
    <pbcast.STABLE stability_delay="1000" desired_avg_gossip="50000"
                   max_bytes="8m"/>
    <pbcast.GMS print_local_addr="true" join_timeout="3000"
                view_bundling="true"/>
    <MFC max_credits="2M"
         min_threshold="0.4"/>
    <FRAG2 frag_size="60K"  />
    <pbcast.STATE_TRANSFER  />
    <CENTRAL_LOCK />
    <COUNTER/>
</config>
```
在此示例里，如果环境变量KUBE_NAMESPACE可用，我们会使用它所对应的值，否则我们使用默认值jgroups-example。我也可以通过设置标签来更加精确的搜索其他的JGroup成员。下面是jgrups-kubernetes的github页提供的示例。
```xml
<org.jgroups.protocols.kubernetes.KUBE_PING
     port_range="1"
     namespace="${KUBE_NAMESPACE:production}"
     labels="${KUBE_LABEL:cluster=nyc}"
```
现在我们来通过deployment文件构建一个docker镜像：
```yaml
apiVersion: apps/v1beta2
kind: Deployment
metadata:
  name: jgroups
  namespace: jgroups
  labels:
    app: jgroups
spec:
  replicas: 2
  selector:
    matchLabels:
      app: jgroups
  template:
    metadata:
      labels:
        app: jgroups
    spec:
      containers:
      - name: jgroups
        image: jgroups-server:v1
        resources:
          limits:
            memory: "538Mi"
        env:
        - name: JAVA_OPTS
          value: "-Xmx512m -Xms512m -Djava.net.preferIPv4Stack=true"
        - name: KUBE_NAMESPACE
          value: "jgroups"
        ports:
        - containerPort: 8080
```
对我来说比较重要的一点是设置启用IPv4，因为如果不这样的话，它会去绑定一个IPv6地址导致打开端口的时候会失败。
现在我们看到，在集群中运行的两个副本已经可以发现彼此了。首先它们会调用kubernetes API去询问集群中的其它现有成员。
```
# the first server only finds itself
2017-11-01 11:17:01.988  INFO 1 --- [           main] o.j.protocols.kubernetes.KUBE_PING       : getPods(jgroups, null) = [Pod{name='jgroups-755dd4cbd9-s6br2', ip='10.244.1.9', parentDeployment='null'}]

# the second server finds itself and the first server
2017-11-01 11:18:02.710  INFO 1 --- [bd9-9xklr-54150] o.j.protocols.kubernetes.KUBE_PING       : getPods(jgroups, null) = [Pod{name='jgroups-755dd4cbd9-9xklr', ip='10.244.1.10', parentDeployment='null'}, Pod{name='jgroups-755dd4cbd9-s6br2', ip='10.244.1.9', parentDeployment='null'}]
```
现在如果我们查看输出，可以看到它们已经可以彼此进行通信了：
```
# first server sends a message and receives it
2017-11-01 11:18:25.295  INFO 1 --- [pool-1-thread-1] ication$$EnhancerBySpringCGLIB$$b6a568ed : Send message '9fbfe381-d9f0-48ed-97a0-d78a150ad0ae'
received message from: jgroups-755dd4cbd9-s6br2-20315 with content: 9fbfe381-d9f0-48ed-97a0-d78a150ad0ae

# the second server only receives this message
received message from: jgroups-755dd4cbd9-s6br2-20315 with content: 9fbfe381-d9f0-48ed-97a0-d78a150ad0ae
```
原文链接https://koudingspawn.de/jgroups-on-kubernetes/
