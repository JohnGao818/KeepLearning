> 在前端的开发工作中，数组是最常用的数据结构，我们经常会遇到对数组进行增删改查的情况。值得庆幸的是，js提供了非常丰富的方法让我们来处理数组。
### 创建数组
#### 字面量和构造器
```javascript
    // 字面量
    let array1 = [1,2,3];
    /** 构造函数
    * 当只有一个数字类型的传参时，会生成一个指定长度的空数组
    * 传参大于1时，按顺序生成一个包含所有入参的数组
    */
    let array2 = new Array(); // array2：[]
    let array3 = new Array(2); // array3：[,]
    let array4 = new Array(1,2); // array4：[1,2]
```
#### `Array.of()`
```javascript
interface ArrayConstructor {
    /**
     * Creates an array from an array-like object.
     * 从一个类数组对象创建数组
     * @param arrayLike An array-like object to convert to an array.
     */
    from<T>(arrayLike: ArrayLike<T>): T[];

    /**
     * Creates an array from an iterable object.
     * 从一个可迭代对象创建数组
     * @param arrayLike An array-like object to convert to an array.
     * @param mapfn A mapping function to call on every element of the array.
     * @param thisArg Value of 'this' used to invoke the mapfn.
     */
    from<T, U>(arrayLike: ArrayLike<T>, mapfn: (v: T, k: number) => U, thisArg?: any): U[];

    /**
     * Returns a new array from a set of elements.
     * 从一组元素创建一个新的数组
     * @param items A set of elements to include in the new array object.
     */
    of<T>(...items: T[]): T[];
}
```
```javascript
    // 类数组对象，key是number类型，并且拥有length属性
    let obj = {0: 'a', 1: 'b', 2:'c', length: 3};
    let array = Array.from(obj); // ['a','b','c'];

    // 部署了 Iterator接口的数据结构 比如:字符串、Set、NodeList对象
    let array = Array.from('hello'); // ['h','e','l','l','o']
    let array = Array.from(new Set(['a','b'])); // ['a','b']

    let array = Array.of(1, 2, 3); // [1,2,3]
    let array = Array.of(3); // [3]
```
### 数组原型上的方法
#### 改变原数组的方法（9个）
##### sort() 对数组进行排序
```js
    /**
     * Sorts an array.
     * 对数组排序
     * @param compareFn Function used to determine the order of the elements. It is expected to return
     * a negative value if first argument is less than second argument, zero if they're equal and a positive
     * value otherwise. If omitted, the elements are sorted in ascending, ASCII character order.
     * 通过此函数可以指定元素的顺序，根据该方法的返回值情况，sort会做出如下判断，负数：第一个参数小于第二个参数；零：第一个参数等于第二个参数；正数：第一个参数大于第二个参数；如果不指定此函数，默认以ASCII码升序排列。
     */
    sort(compareFn?: (a: T, b: T) => number): this;
```
```js
    // 字符串数组
    let array = ["Banana", "Orange", "Apple", "Mango"];
    a.sort(); // ["Apple","Banana","Mango","Orange"]
    // 数字数组，可以看到，默认情况下并没有按照我们常规的预想进行排序,必须通过参数指定排序规则
    let array = [10, 1, 3, 20, 25, 8];
    a.sort(); // [1,10,20,25,3,8]
    a.sort((a,b) => a-b); // [1,3,8,10,20,25]
    a.sort((a,b) => b-a); // [25,20,10,8,3,1]
```
##### push() 向数组的末尾添加元素
```js
    /**
     * Appends new elements to an array, and returns the new length of the array.
     * 向数组的末尾添加新元素，返回数组的新长度
     * @param items New elements of the Array.
     */
    push(...items: T[]): number;
```

```js
    let array1 = [1,2,3];
    array1.push(4); // [1,2,3,4]
    let array2 = [1,2,3];
    array2.push(4,5,6); // [1,2,3,4,5,6
```
##### pop() 删除一个数组中的最后的一个元素并返回此元素
通过与push方法组合使用，可以实现出栈和入栈操作
```js
    /**
     * Removes the last element from an array and returns it.
     * 移出数组的最后一个元素并返回此元素
     */
    pop(): T | undefined;
```

```js
    let array = [1,2,3];
    let el = array.pop();
    /**
    * array: [1,2]
    * el: 3
    */
```

##### shift() 删除数组的第一个元素并返回此元素
```js
    let array = [1,2,3];
    let el = array.shift();
    /**
    * array: [2,3]
    * el: 1
    */
```


##### unshift() 向数组开头插入元素
向数组开头插入元素，并返回新的数组长度
unshift方法的效率要低于push，原因是向数组开头插入元素时，原数组所有元素都要改变下标。
```js
    let array = [1,2,3];
    array.unshift(0); // [0,1,2,3]
    array.unshift(-2, -1); // [-2,-1,0,1,2,3]
```

##### reverse() 反转数组中元素的顺序
函数签名：`reverse(): T[];`
定义：反转数组中元素的顺序
```js
    let array = [1,2,3];
    array.reverse(); // [3,2,1]
```

#### splice() 从数组中删除元素
函数签名：

`splice(start: number, deleteCount?: number): T[];`

`splice(start: number, deleteCount: number, ...items: T[]): T[];`

参数：

start： 以0为开始位置，从该参数指定的位置开始,负数表示倒数

deleteCount： 删除元素的个数

items： 将被删除的元素替换成的元素

```js
    let array1 = [1,2,3,4,5];
    array1.splice(0, 3, 0); // [0,4,5]
    let array2 = [1,2,3,4,5];
    array2.splice(0, 3, 0, 0, 0, 0); // [0,0,0,0,4,5]
    let array3 = [1,2,3,4,5];
    array3.splice(-2, 2); // [1,2,3]
```

#### ES6: copyWithin() 指定位置的元素复制到其他位置
函数签名：

`copyWithin(target: number, start: number, end?: number): this;`

参数：

target: 被替换元素的开始位置,负数表示倒数

start：待复制元素的开始位置,负数表示倒数

end：待复制元素的结束位置（不包含此位置元素），默认为数组长度,负数表示倒数

兼容性：
```js
    let array1 = [1,2,3,4,5];
    array1.copyWithin(0, 2, 4); // [3,4,3,4,5]
    let array2 = [1,2,3,4,5];
    array2.splice(0, -3, -1); // [3,4,3,4,5]
    let array3 = [1,2,3,4,5];
    array3.splice(-2, 2); // [1,2,3]
```

#### ES6: fill() 填充数组
函数签名：

`fill(value: T, start?: number, end?: number): this;`

参数：

value：需要填充的值

start：填充的开始位置，负数表示倒数

end：填充的结束位置，负数表示倒数

```js
    let array1 = [1,2,3];
    array1.fill(0); // [0,0,0]
    let array2 = [1,2,3];
    array2.fill(0, 1, 2); // [1,0,2]
    let array3 = [1,2,3,4];
    array3.fill(0, -2, -1); // [1,2,0,4]
```
