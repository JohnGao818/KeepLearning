> 在前端的开发工作中，数组是最常用的数据结构，我们经常会遇到对数组进行增删改查的情况。值得庆幸的是，js提供了非常丰富的方法让我们来处理数组。
## 创建数组
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
#### `Array.from()` 从一个类数组对象创建数组
##### 定义
从一个类数组对象创建数组
##### 签名
`from<T, U>(arrayLike: ArrayLike<T>, mapfn: (v: T, k: number) => U, thisArg?: any): U[];`
##### 参数
`arrayLike`：类数组对象，拥有length属性，且其他的键都是number类型

`mapfn`：用处理数组中的元素，以此方法的返回值作为最终数组中的元素

`thisArg`：回调函数中的this绑定的对象
```js
    // 类数组对象，key是number类型，并且拥有length属性
    let obj = {0: 'a', 1: 'b', 2:'c', length: 3};
    let array = Array.from(obj); // ['a','b','c'];

    // 部署了 Iterator接口的数据结构 比如:字符串、Set、NodeList对象
    let array = Array.from('hello'); // ['h','e','l','l','o']
    let array = Array.from(new Set(['a','b'])); // ['a','b']
```

#### `Array.of()` 从一个类数组对象创建数组
##### 定义
从一个类数组对象创建数组
##### 签名
`of<T>(...items: T[]): T[];`
##### 参数
`items`：可以是多个数组或者元素

```js
    let array = Array.of(1, 2, 3); // [1,2,3]
    let array = Array.of(3); // [3]
```

## 数组原型上的方法
### 改变原数组的方法（9个）
#### `sort` 对数组进行排序
##### 定义：
对数组进行排序
##### 签名：
`sort(compareFn?: (a: T, b: T) => number): this;`
##### 参数：
`compareFn`：通过此函数可以指定元素的顺序，根据该方法的返回值情况，sort会做出如下判断，负数：第一个参数小于第二个参数；零：第一个参数等于第二个参数；正数：第一个参数大于第二个参数；如果不指定此函数，默认以ASCII码升序排列。

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
#### `push` 向数组的末尾添加元素
##### 定义：
向数组的尾部添加元素
##### 签名：
`push(...items: T[]): number;`
##### 参数：
`items`：需要添加的元素

```js
    let array1 = [1,2,3];
    array1.push(4); // [1,2,3,4]
    let array2 = [1,2,3];
    array2.push(4,5,6); // [1,2,3,4,5,6
```
#### `pop` 删除一个数组中的最后的一个元素并返回此元素
##### 定义：
移出数组的最后一个元素并返回此元素
##### 签名：
`pop(): T | undefined;`

```js
    let array = [1,2,3];
    let el = array.pop();
    /**
    * array: [1,2]
    * el: 3
    */
```
**通过与push方法组合使用，可以实现出栈和入栈操作**

#### `shift` 删除数组的第一个元素并返回此元素
##### 定义：
删除数组的第一个元素并返回此元素
##### 签名：
`shift(): T | undefined;`

```js
    let array = [1,2,3];
    let el = array.shift();
    /**
    * array: [2,3]
    * el: 1
    */
```


#### `unshift` 向数组开头插入元素
##### 定义：
向数组开头插入元素，并返回新的数组长度
##### 签名：
`unshift(...items: T[]): number;`
##### 参数：
`items`：需要添加的元素,可以是多个数组或者元素
```js
    let array = [1,2,3];
    array.unshift(0); // [0,1,2,3]
    array.unshift(-2, -1); // [-2,-1,0,1,2,3]
```
unshift方法的效率要低于push，原因是向数组开头插入元素时，原数组所有元素都要改变下标。
#### `reverse` 反转数组中元素的顺序
##### 定义：
反转数组中元素的顺序
##### 签名：
`reverse(): T[];`

```js
    let array = [1,2,3];
    array.reverse(); // [3,2,1]
```

#### splice() 从数组中删除元素
##### 函数签名：
`splice(start: number, deleteCount?: number): T[];`

`splice(start: number, deleteCount: number, ...items: T[]): T[];`

##### 参数：

`start`： 以0为开始位置，从该参数指定的位置开始,负数表示倒数

`deleteCount`： 删除元素的个数

`items`： 将被删除的元素替换成的值，可以是多个数组或者元素

```js
    let array1 = [1,2,3,4,5];
    array1.splice(0, 3, 0); // [0,4,5]
    let array2 = [1,2,3,4,5];
    array2.splice(0, 3, 0, 0, 0, 0); // [0,0,0,0,4,5]
    let array3 = [1,2,3,4,5];
    array3.splice(-2, 2); // [1,2,3]
```

#### ES6: copyWithin() 指定位置的元素复制到其他位置
##### 定义：

##### 签名：
`copyWithin(target: number, start: number, end?: number): this;`

##### 参数：
`target`: 被替换元素的开始位置,负数表示倒数

`start`：待复制元素的开始位置,负数表示倒数

`end`：待复制元素的结束位置（不包含此位置元素），默认为数组长度,负数表示倒数

##### 兼容性：

```js
    let array1 = [1,2,3,4,5];

    array1.copyWithin(0, 2, 4); // [3,4,3,4,5]
    let array2 = [1,2,3,4,5];
    array2.splice(0, -3, -1); // [3,4,3,4,5]
    let array3 = [1,2,3,4,5];
    array3.splice(-2, 2); // [1,2,3]
```

#### `ES6: fill` 填充数组
##### 函数签名：
`fill(value: T, start?: number, end?: number): this;`
##### 参数：
`value`：需要填充的值

`start`：填充的开始位置，负数表示倒数

`end`：填充的结束位置，负数表示倒数

```js
    let array1 = [1,2,3];
    array1.fill(0); // [0,0,0]
    let array2 = [1,2,3];
    array2.fill(0, 1, 2); // [1,0,2]
    let array3 = [1,2,3,4];
    array3.fill(0, -2, -1); // [1,2,0,4]
```
### 不改变原数组的方法(8个):
#### `slice` 浅拷贝数组的元素
##### 定义： 
返回一个数组从指定的开始位置到结束位置（不包含结束位置元素）的一个浅拷贝
##### 签名：
`slice(start?: number, end?: number): T[];`
##### 参数：
`start`： 指定的开始位置，默认为0；

`end`：指定的结束位置，不含此位置元素，默认为数组末尾，但取默认值时可以包含数组末尾元素；


```js
    let array1 = [1,2,3,4,5];
    let arrayCopy = array1.slice(); //arrayCopy: [1,2,3,4,5]
    let array2 = [1,2,3,4,5];
    let arrayCopy = array2.slice(0,2); //arrayCopy: [1,2]
    let array3 = [1,2,3,4,5];
    let arrayCopy = array3.slice(-3,-1); //arrayCopy: [3,4]
    // 浅拷贝意味着修改被拷贝的数组中对象类型的数据时，会改变原数组中的对象
    let array4 = [{name: 'John', age: 26},{name: 'Alice',age: 25}];
    let arrayCopy = array4.slice(0,1);
    /**
    * array4: [{name: 'John', age: 26},{name: 'Alice',age: 25}]
    * arrayCopy: [{name: 'John', age: 26}]
    */
    arrayCopy[0].age = 30;
    /**
    * array4: [{name: 'John', age: 30},{name: 'Alice',age: 25}]
    * arrayCopy: [{name: 'John', age: 30}]
    */
```

#### `join` 数组转字符串
##### 定义：
以指定的字符作为分隔符生成包含数组所有元素的字符串
##### 签名：
`join(separator?: string): string;`
##### 参数：
`separator`：分隔符，默认为逗号

```js
    let array = ['John', 'Alice', 'Rose'];
    let arrayString1 = array.join(); // 'John,Alice,Rose'
    let arrayString2 = array.join(';'); // 'John;Alice;Rose'
    // 当数组中包含子数组时
    let array = [['John', 'Mike'], 'Alice', 'Rose'];
    let arrayString = array.join(); // 'John,Mike,Alice,Rose'
    // 当数组中包含对象时
    let array = [{name: 'John', age: 26}, 'Alice', 'Rose'];
    let arrayString = array.join(); // '[object Object],Alice,Rose'
```

#### `cancat` 合并数组
##### 定义：
合并两个或更多数组，返回一个新数组
##### 签名：
`concat(...items: (T | ConcatArray<T>)[]): T[];`
##### 参数：
`items`： ，或者包含join和slice方法的类数组对象

```js
    let array = ['John', 'Alice', 'Rose'];
    let arrayString1 = array.concat('Mike', 'Alex'); // ['John', 'Alice', 'Rose','Mike', 'Alex']
    let arrayString2 = array.concat(['Mike', 'Alex'], ['Eric']); // ['John', 'Alice', 'Rose','Mike', 'Alex','Eric']
    // 当被合并的数组中包含对象类型元素时，合并时执行的依然是浅拷贝
    let array1 = ['Rose','Mike', 'Alex'];
    let array2 = [{name: 'John', age: 26},{name: 'Alice',age: 25}];
    let arrayConcat = array2.concat(array1);
    arrayConcat[0].age = 30;
    /**
    * arrayConcat: [{name: 'John', age: 30},{name: 'Alice',age: 25},'Rose','Mike', 'Alex']
    * array2: [{name: 'John', age: 30},{name: 'Alice',age: 25}]
    */
```

#### `indexOf` 查找数组第一次出现某元素的位置
##### 定义：
从指定位置开始，返回数组中第一一次出现某元素的下标,如果不存在，返回-1；
##### 签名：
`indexOf(searchElement: T, fromIndex?: number): number;`
##### 参数
`searchElement`：要搜索的元素

`fromIndex`：开始搜索的位置

```js
    let array = ['John', 'Alice', 'Rose', 'John'];
    let index = array.indexOf('John'); // 0
```

#### `lastIndexOf` 查找数组最后一次出现某元素的位置
##### 定义：
从指定位置开始，返回数组中最后一次出现某元素的下标,如果不存在，返回-1；（会从数组后面往前查找）
##### 签名：
`lastIndexOf(searchElement: T, fromIndex?: number): number;`
##### 参数
`searchElement`：要搜索的元素

`fromIndex`：开始搜索的位置,默认为0，负数代表倒数

```js
    let array = ['John', 'Alice', 'Rose', 'John'];
    let index = array.lastIndexOf('John'); // 3
```

#### `toString` 数组转字符串
##### 定义：
将指定数组转为字符串
##### 签名：
`toString(): string;`

```js
    let array = ['John', 'Alice', 'Rose'];
    let arrayString = array.toString(); // 'John,Alice,Rose'
    // 数组中包含子数组
    let array = [['John','Mike'], 'Alice', 'Rose'];
    let arrayString = array.toString(); // 'John,Mike,Alice,Rose'
    // 数组中包含对象
    let array = [{name: 'John', age: 26}, 'Alice', 'Rose'];
    let arrayString = array.toString(); // '[object Object],Alice,Rose'
```
此方法与join类似，但是join可以自定义分隔符，更加灵活。

#### `toLocaleString` 数组转字符串
##### 定义：
通过调用数组元素的`toLocaleString`方法，将数组转为字符串,
##### 签名：
`toLocaleString(): string;`

```js
    let array = ['John', 'Alice', 'Rose'];
    let arrayString = array.toLocaleString(); // 'John,Alice,Rose'
    // 数组中包含子数组
    let array = [['John','Mike'], 'Alice', 'Rose'];
    let arrayString = array.toLocaleString(); // 'John,Mike,Alice,Rose'
    // 数组中包含对象
    let array = [{name: 'John', age: 26}, 'Alice', 'Rose'];
    let arrayString = array.toLocaleString(); // '[object Object],Alice,Rose'
    // 数组中的对象拥有toLocaleString方法
    let person = {
        name: 'John',
        age: 26,
        toLocaleString: function() {
            return 'name: ' + this.name + '; age: ' + this.age;
        }
    }
    let array = [person, new Date()];
    let arrayString = array.toLocaleString(); // "name: John; age: 26,2020/6/20 上午11:32:16"
```

#### `ES7 includes` 查找数组中是否包含某元素
##### 定义：
在数组中搜索指定元素，返回一个布尔值
##### 签名：
`includes(searchElement: T, fromIndex?: number): boolean;`
##### 参数：
`searchElement`： 要搜索的元素

`fromIndex`：搜索的开始位置，默认为0
##### 兼容性

```js
    let array = ['John', 'Alice', 'Rose'];
    let a = array.includes('John'); // true
    let b = array.includes('John', 1); // false
```
IE浏览器暂不支持此方法，可以使用indexOf方法代替

### 遍历数组方法（12个）
#### `forEach` 遍历数组
##### 定义：
按下标顺序为数组中的每一项执行一次回调函数
##### 签名：
`forEach(callbackfn: (value: T, index: number, array: T[]) => void, thisArg?: any): void;`
##### 参数：
`callbackfn`：回调函数，包含三个参数，value: 本次遍历的元素，index：本次遍历的下标，array：数组对象本身

`thisArg`：回调函数中的this绑定的对象

##### 注意：
+ 无法中途跳出循环
+ 无返回值
+ 对于空数组是不会执行回调函数的
+ 对于已在迭代过程中删除的元素，或者空元素会跳过回调函数
+ 遍历次数再第一次循环前就会确定，再添加到数组中的元素不会被遍历。
+ 如果已经存在的值被改变，则传递给 callback 的值是遍历到他们那一刻的值。

#### `every` 检测数组所有元素是否都符合判断条件
##### 定义：
检测数组所有元素是否都符合回调函数中定义的条件，如果数组中检测到有一个元素不满足，则整个表达式返回 false，且剩余的元素不会再进行检测。必须所有元素都满足条件，才会返回true。
##### 签名：
`every(callbackfn: (value: T, index: number, array: T[]) => unknown, thisArg?: any): boolean;`
##### 参数：
`callbackfn`：回调函数，包含三个参数，value: 本次遍历的元素，index：本次遍历的下标，array：数组对象本身

`thisArg`：回调函数中的this绑定的对象

```js
    let array = [
        {name: 'John', age: 26},
        {name: 'Alice', age: 25},
        {name: 'Rose', age: 28}
    ];
    // 判断所有人的年龄是否都小于30
    let result = array.every((person) => person.age < 30); // true
```

#### `some` 检测数组中的是否有满足判断条件的元素
##### 定义：
检测数组中的是否有满足判断条件的元素，当遍历到有满足判断条件的元素时，返回true，剩下的元素不再遍历。当所有元素都不满足时，返回false；
##### 签名：
`some(callbackfn: (value: T, index: number, array: T[]) => unknown, thisArg?: any): boolean;`
##### 参数：
`callbackfn`：回调函数，包含三个参数，value: 本次遍历的元素，index：本次遍历的下标，array：数组对象本身

`thisArg`：回调函数中的this绑定的对象

```js
    let array = [
        {name: 'John', age: 26},
        {name: 'Alice', age: 25},
        {name: 'Rose', age: 35}
    ];
    // 判断是否有人的年龄小于30
    let result = array.every((person) => person.age < 30); // true
```

#### `filter` 从数组中过滤出符合条件的元素
##### 定义
从数组中过滤出符合条件的元素，将这些元素组合成一个新的数组，进行返回
##### 签名
`filter(callbackfn: (value: T, index: number, array: T[]) => unknown, thisArg?: any): T[];`
##### 参数：
`callbackfn`：回调函数，包含三个参数，value: 本次遍历的元素，index：本次遍历的下标，array：数组对象本身

`thisArg`：回调函数中的this绑定的对象

```js
    let array = [
        {name: 'John', age: 26},
        {name: 'Alice', age: 25},
        {name: 'Rose', age: 35}
    ];
    // 筛选出年龄小于30岁的人
    let result = array.filter((person) => person.age < 30); // [{name: 'John', age: 26},{name: 'Alice', age: 25}]
```

#### `map` 对数组中的每个元素进行处理，返回新的数组
##### 定义
遍历数组中的每一个元素，执行回调函数，将回调函数返回的新元素组合成一个新数组进行返回
##### 签名
`map<U>(callbackfn: (value: T, index: number, array: T[]) => U, thisArg?: any): U[];`
##### 参数：
`callbackfn`：回调函数，包含三个参数，value: 本次遍历的元素，index：本次遍历的下标，array：数组对象本身

`thisArg`：回调函数中的this绑定的对象

```js
    let array = [
        {name: 'John', age: 26},
        {name: 'Alice', age: 25}
    ];
    // 筛选出年龄小于30岁的人
    let result = array.filter((person) => {name: person.name, age: person.age, country: 'China'}); // [{name: 'John', age: 26, country: 'China'},{name: 'Alice', age: 25, country: 'China'}]
```

#### `reduce` 为数组提供累加器，合并为一个值
##### 定义
遍历数组中的每一个元素，执行回调函数，其中本次遍历中回调函数返回的值将作为下次回调函数的入参，将最后一次遍历中回调函数的返回值作为reduce函数的返回值
##### 签名
`reduce(callbackfn: (previousValue: T, currentValue: T, currentIndex: number, array: T[]) => T, initialValue: T): T;`
##### 参数：
`callbackfn`：回调函数，包含四个个参数，previousValue：上次遍历回调函数的返回值，currentValue: 本次遍历的元素，currentIndex：本次遍历的下标，array：数组对象本身

`initialValue`：首次遍历回调函数previousValue的值

```js
    let array = [
        {name: 'John', age: 26},
        {name: 'Alice', age: 25}
    ];
    // 统计所有人年龄之和
    let result = array.reduce((previousValue, person) => previousValue + person.age); // 51
```

#### `reduceRight` 为数组提供累加器，合并为一个值
除遍历方向相反外，其他功能与reduce完全一致

#### `find` 根据条件从数组中寻找元素
##### 定义
根据回调函数指定的条件，在数组中寻找第一个符合条件的元素，并返回此元素。如果没有找到，返回undefined
##### 签名
`find(predicate: (value: T, index: number, obj: T[]) => unknown, thisArg?: any): T | undefined;`
##### 参数：
`callbackfn`：回调函数，包含三个参数，value: 本次遍历的元素，index：本次遍历的下标，obj：数组对象本身

`thisArg`：回调函数中的this绑定的对象

```js
    let array = [
        {name: 'John', age: 26},
        {name: 'Alice', age: 25}
    ];
    // 寻找名字为John的人
    let result = array.find((person) => person.name === 'John'); // {name: 'John', age: 26}
```

#### `findIndex` 根据条件从数组中寻找某元素的下标
##### 定义
根据回调函数指定的条件，在数组中寻找第一个符合条件的元素，并返回此元素的下标。如果没有找到，返回-1
##### 签名
`findIndex(predicate: (value: T, index: number, obj: T[]) => unknown, thisArg?: any): number;`
##### 参数：
`callbackfn`：回调函数，包含三个参数，value: 本次遍历的元素，index：本次遍历的下标，obj：数组对象本身

`thisArg`：回调函数中的this绑定的对象

```js
    let array = [
        {name: 'John', age: 26},
        {name: 'Alice', age: 25}
    ];
    // 寻找名字为John人的下标
    let result = array.findIndex((person) => person.name === 'John'); // 0
```

#### `keys`、`values`、`entries` 遍历键名、遍历键值、遍历键名+键值
##### 定义
返回一个可遍历对象，分别包含数组的键名，键值，键名+键值
##### 签名
`keys(): IterableIterator<number>;`

`values(): IterableIterator<T>;`

`entries(): IterableIterator<[number, T]>;`

```js
    let array = [
        {name: 'John', age: 26},
        {name: 'Alice', age: 25}
    ];
    let arrayKeys = array.keys();
    for (let key of arrayKeys) {
        console.log(key); // 0 1 
    }
    let arrayValues = array.values();
    for (let value of arrayValues) {
        console.log(value.name); // John Alice
    }
    let arrayEntries = array.entries();
    for (let [key, value] of arrayEntries) {
        console.log([key, value.name]); // [0, 'John'] [1, 'Alice']
    }
```
### 结语
js语言针对数组这种数据结构提供了丰富的操作方法，熟练的使用可以大大提高开发效率，并且使得代码的编写更具易读性，可维护性。

