排序：
内部排序：在内存中排序。外部排序：在内存和外存中不断移动
对n个关键字进行基于比较的排序，比较次数为log2(n!)向上取整
### 插入排序
#### 直接插入排序
```c++
void Insert_Sort(int A[], int n) {
    int i, j;
    for(i = 1; i <= n; i++) {
        A[0] = A[i];
        for (j = i - 1; A[j] > A[0]; j--) {
            A[j+1] = A[j];
        }
        A[j+1] = A[0];
    }
}
```

性能分析：
空间复杂度：O(1);
时间复杂度：
最好情况：O(n);
最坏情况：O(n^2);
平均：O(n^2);
稳定性：稳定;
适用性：顺序存储和链式存储

#### 折半插入排序
```c++
void Binary_insert(int A[], int n)
{
    int i, j, left, right, mid;
    for (i = 2; i <= n; i++)
    {
        A[0] = A[i];
        left = 1, right = i - 1;
        while (right >= left)
        {// 根据折半查找找到每趟排序元素的插入位置
            mid = (left + right) / 2;
            if (A[mid] > A[0])
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        for (j = i; j > right; j--)
        {
            A[j] = A[j - 1];
        }
        A[right + 1] = A[0];
    }
}
```

性能分析：
折半插入排序比直接插入排序节省了元素比较次数，但是元素移动次数未变，故时间复杂度仍为O(n^2);
稳定性：稳定

折半查找：
```c++
int Binary_search(int A[], int left, int right, int m) {
    if (left == right && A[left] != m) {
        return 0;
    }
    int mid = left + (right - left) / 2;
    if (A[mid] > m) {
        return Binary_search(A, left, mid - 1, m);
    } else if (A[mid] < m) {
        return Binary_search(A, mid + 1, right, m);
    } else if (A[mid] = m) {
        return mid;
    }
}

int Binary_search2(int A[], int n, int m) {
    int left = 1, right = n;
    int mid = left + (right - left) / 2;
    while(left != right && A[mid] != m) {
        if (A[mid] > m) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
        mid = left + (right - left) / 2;
    }
    if (A[mid] == m) {
        return mid;
    } else {
        return 0;
    }
}
```

### 交换排序
#### 冒泡排序

```c++
void Bubble_Sort(int A[], int n) {
    int i, j, temp, flag;
    for (i = 1; i<n; i++) {
        for (j = n; j > i; j--) {
            if (A[j-1] > A[j]) {
                temp = A[j-1];
                A[j-1] = A[j];
                A[j] = temp;
            }
        }
    }
}
```

性能分析：
空间复杂度：O(1);
时间复杂度：O(n^2);
稳定性: 稳定

快速排序:
```c++
int Partition(int A[], int left, int right) {
    int pivo = A[left], i = left, j = right;
    bool leftFlag = false;
    while(i < j) {
        if (leftFlag) {
            if (A[i] > pivo) {
                A[j] = A[i];
                j--;
                leftFlag = false;
            } else {
                i++;
            }
        } else {
            if (A[j] < pivo) {
                A[i] = A[j];
                i++;
                leftFlag = true;
            } else {
                j--;
            }
        }
    }
    A[i] = pivo;
    return i;
}
```

性能分析：
空间复杂度：O(log2n)
时间复杂度：最好O(nlog2n),最坏O(n^2)
稳定性： 不稳定

### 选择排序
#### 简单选择排序
```c++
void Select_Sort(int A[], int n) {
    int min, temp, i, j;
    for (i = 1; i <= n; i++) {
        min = i;
        for (j = i + 1; j <= n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        if (min != i) {
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
        }
    }
}
```

性能分析：
空间复杂度：O(1)
时间复杂度：O(n^2)
稳定性：不稳定

#### 堆排序

```c++
void HeapAdjust(int A[], int k, int n) {
    A[0] = A[k];
    for (int i = 2*k; i <= n; i*=2 ) {
        if (i < n && A[i] < A[i+1]) {
            i++;
        }
        if (A[0] > A[i]) {
            break;
        } else {
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

void BuildMaxHeap(int A[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        HeapAdjust(A, i, n);
    }
}

void Heap_Sort(int A[], int n) {
    BuildMaxHeap(A, n);
    int temp;
    for(int i=n; i>0; i--) {
        temp = A[1];
        A[1] = A[i];
        A[i] = temp;
        HeapAdjust(A, 1, i-1);
    }
}
```

性能分析：
空间复杂度：O(1)
时间复杂度：平均O(nlog2n)
稳定性： 不稳定

归并排序
```c++
void merge(int A[], int left, int mid, int right) {
    int B[right - left + 1];
    int i, j, k;
    for (i = left, j = mid + 1, k = 0; i <= mid && j <= right; k++) {
        if (A[i] < A[j]) {
            B[k] = A[i++];
        } else {
            B[k] = A[j++];
        }
    }
    while(i <= mid) {
        B[k++] = A[i++];
    }
    while(j <= right) {
        B[k++] = A[j++];
    }
    i = left;
    while (i <= right) {
        A[i] = B[i - left];
        i++;
    }
}

void Merge_Sort(int A[], int left, int right) {
    if (right > left) {
        int mid = (left + right) / 2;
        Merge_Sort(A, left, mid);
        Merge_Sort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}
```
性能分析：
空间复杂度：O(n)
时间复杂度：平均O(nlog2n)
稳定性： 稳定

