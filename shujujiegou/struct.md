### 顺序表

1.从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删元素的值。空出的位置由最后一个元素填补，若顺序表为空则显示出错信息并退出运行。

```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}


bool SEEK_MIN(SqList &L, int &elem) {
	if (L.length < 1) {
		return false;
	}
	elem = L.data[0];
	int minIndex = 0;
	for (int i = 1; i < L.length; i++) {
	    if (L.data[i] < elem) {
	        elem = L.data[i];
	        minIndex = i;
	    }
	}
	L.data[minIndex] = L.data[L.length - 1];
	return true;
}

int main()
{
    int arrayTemp[5] = {1,2,3,4,5};
    int min;
    SqList sq = createSqList(arrayTemp, 5);
    bool result = SEEK_MIN(sq, min);
    if (result) {
        printf("min element = %d", min);
    } else {
        printf("Array must not be empty!\n");
    }
    return 0;
}
```

2.设计一个高效算法，将顺序表 L 的所有元素逆置，要求算法的空间复杂度为 0(1)。

```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}



SqList reverse(SqList &L) {
	if (L.length <= 1) {
		return L;
	}
	int cycleTimes = L.length / 2;
    int temp;
	for (int i = 0; i < cycleTimes; i++) {
        temp = L.data[i];
        L.data[i] = L.data[L.length - i - 1];
        L.data[L.length - i - 1] = temp;
	}
	return L;
}

int main()
{
    int arrayTemp[5] = {1,2,3,4,5};
    int min;
    SqList sq = createSqList(arrayTemp, 5);
    reverse(sq);
    for (int i = 0; i < sq.length; i++) {
        printf("sq.data[%d] element = %d\n", i, sq.data[i]);
    }
    return 0;
}
```

3.对长度为n的顺序表L,编写一个时间复杂度为o(n)空间复杂度为0(1)的算法，该算法删除线性表中所有值为x的数据元素。.
```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}



SqList deleteSpecifiedElem(SqList &L, int delElem) {
    int offset = 0; // 当删除元素时，其后元素向前挪动的偏移量
	for (int i = 0; i < L.length; i++) {
        if (L.data[i] == delElem) {
            offset++; // 每删除一个元素时，其后元素向前挪动的偏移量都要加1
        } else {
            L.data[i - offset] = L.data[i];
        }
	}
    L.length -= offset; // 每删除一个元素，顺序表长度减1
	return L;
}

int main()
{
    int arrayTemp[5] = {1,2,3,2,5};
    int min;
    SqList sq = createSqList(arrayTemp, 5);
    deleteSpecifiedElem(sq, 2);
    for (int i = 0; i < sq.length; i++) {
        printf("sq.data[%d] element = %d\n", i, sq.data[i]);
    }
    return 0;
}
```

4.从有序顺序表中删除其值在给定值s与t之间(要求s < t)的所有元素，如果s或t不合理或顺序表为空，则显示出错信息并退出运行。

```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}



SqList deleteRangeElem(SqList &L, int delStart, int delEnd) {
    if (delStart >= delEnd) {
        return L;
    }
    int offset = 0; // 当删除元素时，其后元素向前挪动的偏移量
	for (int i = 0; i < L.length; i++) {
        if (delStart < L.data[i] && L.data[i]  < delEnd) {
            offset++; // 每删除一个元素时，其后元素向前挪动的偏移量都要加1
        } else {
            L.data[i - offset] = L.data[i];
        }
	}
    L.length -= offset; // 每删除一个元素，顺序表长度减1
	return L;
}

int main()
{
    int arrayTemp[5] = {1,2,3,2,5};
    int min;
    SqList sq = createSqList(arrayTemp, 5);
    deleteRangeElem(sq, 1, 3);
    for (int i = 0; i < sq.length; i++) {
        printf("sq.data[%d] element = %d\n", i, sq.data[i]);
    }
    return 0;
}
```

6.从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不同。

```c++
#include <stdio.h>
#define MaxSize 20

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}



SqList unique(SqList &L) {
    int offset = 0;
    for (int i = 0; i < L.length; i++) {
        bool equals = false;
        for (int j = 0; j < i - offset; j++) {
            if (L.data[i] == L.data[j]) {
                offset++;
                equals = true;
                break;
            }
        }
        if (!equals) {
            L.data[i - offset] = L.data[i];
        }
    }
    L.length -= offset;
	return L;
}

int main()
{
    int arrayTemp[5] = {1,2,3,2,5};
    int min;
    SqList sq = createSqList(arrayTemp, 5);
    unique(sq);
    for (int i = 0; i < sq.length; i++) {
        printf("sq.data[%d] element = %d\n", i, sq.data[i]);
    }
    return 0;
}
```

7.将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表。
```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}



SqList concat(SqList &L1, SqList &L2) {
    SqList sq;
    int minSize = L1.length < L2.length ? L1.length : L2.length;
    int i = 0, j = 0;
    while (i < L1.length || j < L2.length) {
        if (i >= L1.length) {
            sq.data[i+j] = L1.data[j];
            j++;
        } else if (j >= L2.length) {
            sq.data[i+j] = L1.data[i];
            i++;
        } else if (L1.data[i] < L2.data[j]) {
            sq.data[i+j] = L1.data[i];
            i++;
        } else {
            sq.data[i+j] = L2.data[j];
            j++;
        }
    }
    sq.length = L1.length + L2.length;
    return sq;
}

int main()
{
    int arrayTemp1[5] = {1,2,13,20,50};
    int arrayTemp2[8] = {0,2,10,21,30,31,40,45};
    SqList sq1 = createSqList(arrayTemp1, 5);
    SqList sq2 = createSqList(arrayTemp2, 8);
    SqList sqConcated = concat(sq1, sq2);
    for (int i = 0; i < sq.length; i++) {
        printf("sq.data[%d] element = %d\n", i, sqConcated.data[i]);
    }
    return 0;
}
```

8.已知在一维数组A[m + n]中依次存放两个线性表(a1, a2, ...., am,)和(b1, b2, ..., bn)。试编写一个函数，将数组中两个顺序表的位置互换，即将(b1, b2, ..., bn)放在(a1, a2, a3, ..., am)的前面。

```c++
#include <stdio.h>
#define MaxSize 20

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}



SqList reverseTwoSubsequence(SqList &L, int firstLength, int secondLength) {
    int longerSubsequence = firstLength < secondLength ? secondLength : firstLength;
    for (int i = 0; i < longerSubsequence; i++) {
        int temp = L.data[firstLength + i];
        L.data[firstLength + i] = L.data[i];
        L.data[i] = temp;
    }
	return L;
}

int main()
{
    int arrayTemp[8] = {1,2,3,2,5,10,0,100};
    SqList sq = createSqList(arrayTemp, 8);
    reverseTwoSubsequence(sq, 2, 6);
    for (int i = 0; i < sq.length; i++) {
        printf("sq.data[%d] element = %d\n", i, sq.data[i]);
    }
    return 0;
}
```

9.线性表(a, a2, a... an)中的元素递增有序且按顺序存储于计算机内。要求设计一算法，完成用最少时间在表中查找数值为x的元素，若找到则将其与后继元素位置相交换，若找不到则将其插入表中并使表中元素仍递增有序。

```c++
#include <stdio.h>
#define MaxSize 20

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}

SqList insert(SqList &L, int elem, int index) {
    for (int i = L.length; i > index; i--) {
        L.data[i] = L.data[i - 1];
    }
    L.data[index] = elem;
    L.length++;
    return L;
}

bool seachElem(SqList &L, int target, int seachStart, int seachEnd) {
    int middleIndex = seachStart + (seachEnd -  seachStart) / 2;
    if (L.data[middleIndex] == target) {
        int temp = L.data[middleIndex + 1];
        L.data[middleIndex + 1] = L.data[middleIndex];
        L.data[middleIndex] = temp;
        return true;
    }else if (L.data[middleIndex] < target) {
        if (seachStart == seachEnd) {
            insert(L, target, middleIndex + 1);
            return false;
        } else {
            seachElem(L, target, middleIndex + 1, seachEnd);
        }
    } else if (L.data[middleIndex] > target) {
        if (seachStart == seachEnd) {
            insert(L, target, middleIndex);
            return false;
        } else {
            seachElem(L, target, seachStart, middleIndex - 1);
        }
    }
}
bool convertOrInsert(SqList &L, int target) {
    return seachElem(L, target, 0, L.length - 1);
}

int main()
{
    int arrayTemp[8] = {1,2,3,4,5,7,8,9};
    SqList sq = createSqList(arrayTemp, 8);
    convertOrInsert(sq, 6);
    for (int i = 0; i < sq.length; i++) {
        printf("sq.data[%d] element = %d\n", i, sq.data[i]);
    }
    return 0;
}
```

10.设将n (n> 1)个整数存放到一维数组R中。设计一个在时间和空间两方面都尽可能高效的算法。将R中保存的序列循环左移p (0< p < n)个位置，即将R中的数据由(X0, X1, ... , Xn-1)变换为(Xp, Xp+1, ... , Xn-1, X0, X1, ... Xp-1) 要求:
1)给出算法的基本设计思想。
2)根据设计思想，采用C或C++或Java语言描述算法;关键之处给出注释。
3)说明你所设计算法的时间复杂度和空间复杂度。

```c++
#include <stdio.h>
#define MaxSize 20

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}

void interchange(SqList &L, int firstIndex, int secondIndex) {
    int temp = L.data[firstIndex];
    L.data[firstIndex] = L.data[secondIndex];
    L.data[secondIndex] = temp;
}

SqList leftShift(SqList &L, int shift) {
    if (shift <= 0 || shift >= L.length) {
        return L;
    }
    int arrayTemp[shift] = {};
    for (int i = 0; i < L.length; i++) {
        if (i < shift) {
            arrayTemp[i] = L.data[i];
        }
        if (i < L.length - shift) {
            L.data[i] = L.data[i + shift];
        }
        if (i >= L.length - shift) {
            L.data[i] = arrayTemp[i - (L.length - shift)];
        }
    }
	return L;
    // 时间复杂度o(n),空间复杂度o(n)
}

int main()
{
    int arrayTemp[8] = {1,2,3,4,5,6,7,8};
    SqList sq = createSqList(arrayTemp, 8);
    leftShift(sq, 2);
    for (int i = 0; i < sq.length; i++) {
        printf("sq.data[%d] element = %d\n", i, sq.data[i]);
    }
    return 0;
}
```

11.一个长度为L (L≥1)的升序序列S,处在第[L/2]个位置的数称为S的中位数。例如，若序列S1=(11, 13,15, 17, 19)，则S1的中位数是15,两个序列的中位数是含它们所有元素的升序序列的中位数。例如，若S2=(2,4,6,8, 20)，则S1和S2的中位数是11。现在有两个等长升序序列A和B，试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列A和B的中位数。要求:
1)给出算法的基本设计思想。
2)根据设计思想，采用C或C++或Java语言描述算法，关键之处给出注释。
3)说明你所设计算法的时间复杂度和空间复杂度。

```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}

int getMedian(SqList &L1, SqList &L2) {
    SqList sq;
    int median;
    int i = 0, j = 0;
    while ((i < L1.length || j < L2.length) && i + j - 2 <= (L1.length + L2.length) / 2) {
        if (L1.data[i] < L2.data[j]) {
            i++;
        } else {
            j++;
        }
    }
    return L1.data[i] < L2.data[j] ? L2.data[j] : L2.data[i];
    // 时间复杂度o(n),空间复杂度o(1)
}

int main()
{
    int arrayTemp1[5] = {1,2,13,20,50};
    int arrayTemp2[5] = {0,2,10,21,30};
    SqList sq1 = createSqList(arrayTemp1, 5);
    SqList sq2 = createSqList(arrayTemp2, 5);
    int median = getMedian(sq1, sq2);
    printf("median = %d\n", median);
    return 0;
}
```

12.已知一个整数序列A=(a0,a1,...,an-1),其中0≤ai<n (0≤ i < n)。若存在ap1=ap2=...=apm=x, 且m>n/2 (0≤pk<n, 1≤k≤m)，则称x为A的主元素。例如A=(0,5,5,3,5,7,5,5),则5为主元素;又如A=(0,5,5,3,5,1,5,7), 则A中没有主元素。假设A中的n个元素保存在一个一维数组中，请设计一个尽可能高效的算法，找出A的主元素。若存在主元素，则输出该元素;否则输出-1。要求:
1)给出算法的基本设计思想。
2)根据设计思想，采用C或C++或Java语言描述算法，关键之处给出注释。
3)说明你所设计算法的时间复杂度和空间复杂度。

```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;  

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}

int getMainElem(SqList &L) {
    int candidate = L.data[0];
    int count = 1;
    for (int i = 1; i < L.length; i++) {
        if (count == 0) {
            candidate = L.data[i];
            count++;
        } else {
            L.data[i] == candidate ? count++ : count--;
        }
    }
    count = 0;
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == candidate && ++count > L.length / 2) {
            return candidate;
        }
    }
    return -1;
    // 时间复杂度o(n),空间复杂度o(1)
}

int main()
{
    int arrayTemp[8] = {0,5,5,3,5,7,5,5};
    SqList sq = createSqList(arrayTemp, 8);
    int mainElem = getMainElem(sq);
    printf("median = %d\n", mainElem);
    return 0;
}
```

13.给定一个含n (n≥1)个整数的数组，请设计一个在时间上尽可能高效的算法，找出数组中未出现的最小正整数。例如，数组{ -5,3,2,3}中未出现的最小正整数是1;数组{1,2,3}中 未出现的最小正整数是4。要求:
1)给出算法的基本设计思想。
2)根据设计思想，采用C或C++语言描述算法，关键之处给出注释。
3)说明你所设计算法的时间复杂度和空间复杂度。

```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;  

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}

SqList bubbleSort(SqList L) {
    for (int i = L.length - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (L.data[j] > L.data[j+1] || L.data[j] <= 0) {
                int temp = L.data[j+1];
                L.data[j+1] = L.data[j];
                L.data[j] = temp;
            }
        }
    }
    for (int i = 0; i < L.length; i++) {
        printf("median = %d,", L.data[i]);
    }
    return L;
}

int getMinimumBesides(SqList &L) {
    SqList sorted = bubbleSort(L);
    for (int i = 0; i<sorted.length; i++) {
        if (sorted.data[i] <= 0 || sorted.data[i] != i+1) {
            return sorted.data[i-1] + 1;
        }
    }
    return sorted.data[sorted.length - 1] + 1;
    // 时间复杂度o(n方),空间复杂度o(1)
}

int main()
{
    int arrayTemp[8] = {0,5,5,3,5,7,5,5};
    SqList sq = createSqList(arrayTemp, 8);
    int minimum = getMinimumBesides(sq);
    printf("median = %d\n", minimum);
    return 0;
}
```


```c++
#include <stdio.h>
#define MaxSize 10

typedef struct{
	int data[MaxSize];
	int length;
}SqList;

SqList createSqList(int *array, int length) {
    SqList sq;
    for (int i = 0; i < length; i++) {
        sq.data[i] = array[i];
    }
    sq.length = length;
    return sq;
}

int getMinimumBesides(SqList &L) {
    int tempArray[L.length] = {0};
    for (int i=0; i < L.length; i++) {
        if (L.data[i] > 0 && L.data[i] <= n) {
            tempArray[i-1] = 1;
        }
    }
    for (int i=0; i < L.length; i++) {
        if (tempArray[i] == 0) {
            return i+1;
        }
    }
    return L.length + 1;
}

int main()
{
    int arrayTemp[8] = {0,5,5,3,5,7,5,5};
    SqList sq = createSqList(arrayTemp, 8);
    int minimum = getMinimumBesides(sq);
    printf("median = %d\n", minimum);
    return 0;
}
```