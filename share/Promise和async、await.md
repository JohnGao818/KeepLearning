> Promise 是一个对象，它代表了一个异步操作的最终完成或者失败。本质上`Promise`是一个函数返回的对象，我们可以在它上面绑定回调函数，这样我们就不需要在一开始把回调函数作为参数传入这个函数了。 --MDN

众所周知，Javascript 语言的执行环境是单线程的，JavaScript 设计一套异步编程方案来避免任务被长时间阻塞。在没有异步编程的情况下，会出现什么问题呢，比如，你要调用后端的一个接口，而该接口的响应时间会很长，在完全同步的情况下，你需要一直等待该接口返回，在等待期间什么都做不了，多亏了异步编程，我们才能在访问网页时，不用把时间浪费在等待请求返回的过程中。
JavaScript 的异步编程方案也经历了逐渐完善的过程，从最初的回调函数，到 es6 中的`Promise`和`Generator`函数，逐渐形成了较为完善的异步编程方案。

### 回调函数

JavaScript 对异步编程实现的本质就是回调函数，js 中的函数是可以通过参数进行传递的，因此可以将异步任务封装为函数，将异步函数通过参数传递给其他函数，因而可以选择再合适的时间点再去执行异步函数。最典型的使用回调函数的场景是`setTimeout`函数。该函数可以对一个回调函数进行延时执行，但程序并不会在此阻塞。
回调函数实现的原理是 js 的事件循环机制，有兴趣可以搜索相关关键词进行了解。
一个简单的示例：

```javascript
    function taskOne() {
        console.log('task one complete!');
    }
    function taskTwo() {
        console.log('task two complete!');
    }
    setTimeout(taskOne, 100);
    taskTwo();
    /**
     * 输出：
     * task two complete!
     * task one complete!
     *
     * 可见任务1并没有被阻塞，任务2会继续被执行，
     * /
```

### Promise

> `Promise`英文直译即承诺，当你交给它一个任务时，它会承诺必然给你一个执行结果。

`Promise`是 es6 中新推出的异步编程解决方案，promise 的本质还是依托于回调函数，针对异步编程的使用场景，进行了重新的设计和封装。在处理异步场景时，更加优雅，灵活。

#### 基本用法

`Promise`的构造函数接收一个函数作为入参，该函数的两个入参分别为`resolve`和`reject`，`resolve`和`reject`又分别代表两个回调函数(虽然有点绕，但你只要以 js 中函数可以作为参数进行传递作为前提，就不难理解了)，resolve 函数的作用是，将 Promise 对象的状态从`pending`变为`resolved`，在异步操作成功时调用，并将异步操作的结果，作为参数传递出去；`reject`函数的作用是，将`Promise`对象的状态从`pending`变为`rejected`，在异步操作失败时调用，并将异步操作报出的错误，作为参数传递出去。

```javascript
    const promise = new Promise(function (resolve, reject) {
        const result = Math.random() > 0.5;
        if (result) {
            resolve('promise执行成功');
        } else {
            reject('promise执行失败');
        }
    });
```

`Promise`实例生成以后，可以用`then`方法分别指定`resolved`状态和`rejected`状态的回调函数（即上述的`resolve`和`reject`函数）。其中`reject`函数是非必选的。

```javascript
    promise.then(function(value) {
            console.log(value);
        }, function(error) {
            console.log(error);
        }
    );
```

或者可以调用`catch`方法来单独传递`rejected`状态的回调函数。

```javascript
    promise.then(function(value) {
            console.log(value);
        }).catch(function(error) {
            console.log(error);
        });
```

下面是一个完整的例子，运行后我们根据输出结果可以看到，在生成 promise 对象时，promise 会立即执行，所以最先输出 promise，then 方法中的回调函数因为是异步的，所以 resolved.会最后输出。

```javascript
    let promise = new Promise(function(resolve, reject) {
        console.log('Promise');
        resolve();
    });

    promise.then(function() {
        console.log('resolved.');
    });
    console.log('Hi!');
    /**
     * Promise
     * Hi!
     * resolved.
     * /
```

#### 链式调用

在实际的开发过程中，我们经常遇到这样的问题，一个异步任务需要依赖另一个的异步任务的执行结果，这种场景常见于接口调用的依赖，即一个接口的入参需要依赖另一个接口返回值，使用回调函数的方式时，我们通常要在一个回调函数中调用另一个回调函数，但是这样写出来的代码，即不美观，也不清晰，而且难以维护。使用 promise 我们则可以通过简单的链式调用来代替回调函数的嵌套，以下实例中的 post 方法是对 xhrrequest 的一个封装，他返回一个`Promise`对象。使得我们可以通过`Promise`的方式来执行接口调用。

```javascript
    post('api/first').then(function(body) {
        return post(body.secondURL);
    }).then(function (body) {
        console.log("resolved: ", body.toString());
    }, function (err){
        console.log("rejected: ", err.toString());
    });
```

我们可以在`then`方法的回调函数中再次返回一个`Promise`对象，这样我们通过链式调用再次调用`then`方法时，我们其实是调用的是这个返回的`promise`的`then`方法，这样我们通过一个同步的编程方式，实现了两个异步任务的依赖执行。至于第二个异步任务是如何在第一个异步任务执行成功后执行的，我们大可不用考虑，`promise`为我们做好了这一切。

#### Promise.all()

`Promise.all()`方法用于将多个 `Promise` 实例，包装成一个新的 `Promise` 实例。

```javascript
    const p = Promise.all([p1, p2, p3]);
```

其中 p 的状态由 p1、p2、p3 决定，分成两种情况。

（1）只有 p1、p2、p3 的状态都变成`fulfilled`，p 的状态才会变成`fulfilled`，此时 p1、p2、p3 的返回值组成一个数组，传递给 p 的回调函数。

（2）只要 p1、p2、p3 之中有一个被`rejected`，p 的状态就变成`rejected`，此时第一个被 reject 的实例的返回值，会传递给 p 的回调函数。

简单理解就是 p 的成功执行需要依赖 p1，p2，p3 全部成功，只要他们中间有一个被 reject，p 就执行失败。比如当我们遇到一段代码的执行需要同时依赖两个接口的返回值时，就可以使用`Promise.all()`。熟悉 rxjs 的朋友，应该会发现，它与`rxjs`中的`forkjoin`操作符的功能类似。

```javascript
    p1 = post('api/first');
    p2 = post('api/first');
    p = Promise.all([p1, p2]);
    p.then(([body1, body2]) => {
        console.log('resolved: ' + body1.toString() + body2.toString());
    }).catch((err) => {
        console.log('reject: ' + err.toString());
    })
```

#### Promise.race()

`Promise.race()`方法同样是将多个 `Promise` 实例，包装成一个新的 `Promise` 实例。

```javascript
    const p = Promise.race([p1, p2, p3]);
```

它与`Promise.all()`的区别是，p 的状态只会随着 p1,p2,p3 中最先状态最先发生变化而变化，简单理解就是只要 p1,p2,p3 中有一个执行完成（不论成功或失败），这时 p 也执行完成（成功与否与这个最先执行完成的 promise 一致）。它与`rxjs`中的`race`操作符功能类似。

下面我们来模拟一个场景用`Promise.race()`来快速解决。在该场景下，只会等待接口 1 秒的调用时间，1 秒之后若接口还没有返回，则认为失败。

```javascript
    p1 = post('api/first');
    p2 = new Promise(function (resolve, reject) {
        setTimeout(() => reject(new Error('request timeout')), 1000)
    });
    p = Promise.race([p1, p2]);
    p.then((body) => {
        console.log('resolved: ' + body.toString();
    }).catch((err) => {
        console.log('reject: ' + err.toString());
    })
```

#### 后记

`Promise`的出现解决了很多异步编程的痛点，但是个人认为还是响应式编程库 rxjs 更为强大一点，`Promise`能实现的功能`rxjs`都能实现，但是`rxjs`却有更为强大的冷热模式，组播模式和丰富的操作符。
