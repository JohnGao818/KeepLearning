#### 从两个场景开始
场景一：
Kristin正在开发一个社区论坛项目，其中有一个需求，需要在前端页面添加一个通知面板，用来实时展示通知信息，比如@某某评论了您的帖子，@某某关注了您，您关注的@某某发表了新的主题帖。Kristin采用了ajax请求轮询方案来实现，首先注册一个定时器，每隔一段时间去调用后端一个接口去获取通知信息。功能上线后，平稳运行。某天论坛的同时在线人数达到峰值，由于服务器配置较低，大量的轮询请求直接导致服务器瘫痪。
场景二：
John正在做一个云计算平台，创建虚拟机是这个平台的一个基本功能，由于虚拟机的创建流程较长，创建接口被设计成异步请求。用户发起创建请求后，立即返回201，告知用户创建正在执行中。待虚拟机创建完成后，需要再次通知用户创建是否成功。但此时由于请求已经结束，无法将创建结果进行反馈。John同样采用了轮询的方案，为了降低服务器的压力，Kristin加大了轮询的时间间隔，但是通知的及时性却被降低了，用户反馈使用体验很不友好。

以上两个案例都暴露了传统HTTP请求的一个缺点。传统的HTTP协议是一种无状态、无连接、单向的应用层协议，请求只能从客户端发起，服务端对请求进行处理和应答。所以传统的HTTP请求无法从服务端主动的向客户端建立通信。在websocket协议被制定之前，大多数web应用的开发者们通常使用与Kristin和John相同的方案--轮询方式，来解决这个问题。
使用轮询方式，客户端和服务端的交互过程如下：

![http](https://user-images.githubusercontent.com/50511900/71141478-35e23780-224f-11ea-905b-d0d8367b33e6.jpg)

由于服务器端无法主动向客户端发送消息，只能由客户端不停的发送请求来询问服务端是否有消息需要发送。以场景二为例，客户端使用轮询方式频繁向服务端发送询问请求。请求过程如下

![communication5](https://user-images.githubusercontent.com/50511900/71175904-94d19c00-22a3-11ea-9423-8959fb5533c0.jpg)

从这个例子很明显的看出这种方案的缺点：
-  为了获取想要的数据，不得不发起大量的无用请求。
-  由于http协议建立在tcp协议的基础之上，每次请求都需要发起[三次握手和四次挥手](https://juejin.im/post/5d9c284b518825095879e7a5)来分别建立和断开连接，不仅浪费时间，而且耗费资源。
-  假如在上次轮询刚结束，服务端就产生了需要推送的数据，必须等到下次轮询开始，数据才能传递出去。在轮询间隔过长的情况下，势必会影响获取数据的及时性。
(除了轮询的方式以外，还有一个http长连接的方案，由于这种方案使用时的局限性较大，在此不再详述。)
### websocket简介
为了解决这个问题，websocket协议被制定出来，随着HTML5语言的普及，websocket技术也越来越被广泛的运用于web项目中。我们首先看一下websocket协议的客户端与服务端交互过程：

![websocket](https://user-images.githubusercontent.com/50511900/71143142-7c866080-2254-11ea-8954-ec7101fc8555.jpg)

websocket协议允许客户端和服务端之间建立全双工通信，以便消息可以从任意一端发送到另一端，另外websocket只需建立一次长连接，连接建立后，消息可以随时在连接通道上进行传递。以场景二为例我们再来看一下，使用websocket以后客户端与服务端的交互场景是什么样的：

![communication4](https://user-images.githubusercontent.com/50511900/71153428-0b56a580-2274-11ea-93a3-9fa2448fbf4f.jpg)

针对这种特定场景，相对于http协议来说，websocket可以弥补它的几乎所有缺陷：
- 只需建立一次连接，消息即可以随时进行双向传递。
- 实时性高，消息一旦产生，可以立即进行传递。

###
websocket需要通过握手阶段来进行协商建立连接，而握手过程是基于http协议的，下面是一份websocket请求握手的报文样例，
```
General:
Request URL: ws://www.temp.com/websocket
Request Method: GET
Status Code: 101 Switching Protocols

Request Headers:
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cache-Control: no-cache
Upgrade: websocket
Connection: Upgrade
Host: www.temp.com
Origin: http://www.temp.com
Pragma: no-cache
Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits
Sec-WebSocket-Key: /T0A9MgjYNR6ABGpahjt9A==
Sec-WebSocket-Version: 13
User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.108 Safari/537.36

Response Headers:
cache-control: no-cache, no-store, max-age=0, must-revalidate
Connection: upgrade
Content-Length: 0
Date: Fri, 20 Dec 2019 08:45:42 GMT
expires: 0
pragma: no-cache
sec-websocket-accept: pS7o7EovuYzU0QKEBimGaczmQ5I=
sec-websocket-extensions: permessage-deflate;client_max_window_bits=15
Server: nginx
upgrade: websocket
x-content-type-options: nosniff
x-frame-options: DENY
x-xss-protection: 1; mode=block
```
从整个请求报文来看，其中针对其中比较重要的几点做下说明：
#### 协议号
websocket请求的协议号为`ws`或`wss`,分别对应http和https
#### 协议升级
header中Upgrade和Connection负责通知服务端进行协议升级，表示客户端想建立的是websocket连接。值得注意的是这两个请求头，不会被代理服务器所传递，如果你需要使用nginx做负载均衡或代理转发，需要请参考详解websocket之四-nginx代理。
#### 同源策略
Origin：源站地址，也可以理解为客户端所在站点的地址，包括协议+地址+端口。
host：目的地址，即请求的服务端地址。
由于websocket请求不被[同源策略](https://segmentfault.com/a/1190000007366644)所限制，为了提高安全性，可以在服务端配置白名单对Origin进行限制。
#### Sec-WebSocket-Key与Sec-WebSocket-Accept
request header中的Sec-WebSocket-Key与response header中的Sec-WebSocket-Accept是一对协同使用的标头。其中Sec-WebSocket-Key是用base64加密的一串随机密钥
Sec-WebSocket-Accept计算过程为：
1. 获取Sec-WebSocket-Key与一串固定的GUID：258EAFA5-E914-47DA-95CA-C5AB0DC85B11进行拼接
2. 用散列算法sha1计算出摘要
3. 将摘要进行base64加密

客户端收到服务端计算出的Sec-WebSocket-Accept后也会采用同样的算法对Sec-WebSocket-Key进行计算，算的值与Sec-WebSocket-Accept进行比较，如果相同则握手成功。
从整个过程来看，这两个标头好像是为了提高安全性而设计，但我们很容易发现这个算法也太简单了吧，Sec-WebSocket-Accept的值也太好伪造了吧。
以下是RFC 6455的中关于这两个标头的解释：
  ```
  The |Sec-WebSocket-Key| header field is used in the WebSocket opening
  handshake.  It is sent from the client to the server to provide part
  of the information used by the server to prove that it received a
  valid WebSocket opening handshake.  This helps ensure that the server
  does not accept connections from non-WebSocket clients (e.g., HTTP
  clients) that are being abused to send data to unsuspecting WebSocket
  servers.
  ```
从中可以看出两个标头的设计初衷其实是为了过滤非预期的请求，因为websocket是通过Upgrade和Connection这两个标头来进行协议的升级，但是这个两个标头很容易在客户端进行手动设置。如果我们在一个http请求中不小心添加了这两个标头，客户端和服务端则会通过Sec-WebSocket-Key和Sec-WebSocket-Accept来再次确认这个请求是否真的是websocket连接。有兴趣的可以参考Stack Overflow上关于此问题的讨论[what-is-sec-websocket-key-for](https://stackoverflow.com/questions/18265128/what-is-sec-websocket-key-for)

#### 安全策略
在实际应用中，我们并不希望客户端不经过认证就对服务端建立连接。握手阶段采用http协议，可以携带cookie或者通过参数传递token。因此可以通过在握手阶段添加权限认证过程，使仅通过授权的客户端才能成功建立连接。

#### demo
下面是一个仿QQ聊天框实现的一个demo，实际效果访问https://johngao818.github.io/website/websocket/simple-websocket-demo.html
```html
<body>
<div class="container">
    <div class="main">
        <h2>Simple Websocket Demo</h2>
        <div class="dialog box-shadow">
            <div class="title">
                <span>echo</span>
            </div>
            <div id="dialogContent" class="content">
            </div>
            <div class="send-box">
                <textarea id="sendText" role="5"></textarea>
                <button id="sendButton" class="send-button">send</button>
            </div>
        </div>
    </div>
</div>
</body>
<script>
    window.onload = function() {
        let socket = new WebSocket('ws://demos.kaazing.com/echo');
        let sendText = document.getElementById('sendText');
        let sendButton = document.getElementById('sendButton');
        let dialogContent = document.getElementById('dialogContent');
        socket.onmessage = function(ev) {
            dialogContent.insertAdjacentHTML('beforeend', `<p class="left"><span class="bubble">${ev.data}</span></p>`)
        };
        sendButton.onclick = function send() {
            let text = sendText.value;
            dialogContent.insertAdjacentHTML('beforeend', `<p class="right"><span class="bubble">${text}</span></p>`)
            socket.send(text);
            sendText.value = '';
        }
    }
</script>
```

