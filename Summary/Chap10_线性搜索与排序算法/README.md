## 知识点总结
本节课内容对应的[PPT](../../PPT/第10章%20线性搜索与排序算法.pdf)
本章内容对应的代码[线性搜索算法.cpp](../../Code/线性搜索算法.cpp)，[排序算法.cpp](../../Code/排序算法.cpp)

快速索引
- [知识点总结](#知识点总结)
- [线性搜索](#线性搜索)
  - [黄金分割法（0.618法）](#黄金分割法0618法)
  - [Fibonacci](#fibonacci)
- [排序算法](#排序算法)
  - [冒泡排序](#冒泡排序)
  - [选择排序](#选择排序)
  - [插入排序](#插入排序)
  - [希尔排序](#希尔排序)
  - [归并排序](#归并排序)
  - [快速排序](#快速排序)
  - [堆排序](#堆排序)

## 线性搜索
首先就是知道什么是线性搜索法

目标：实现 $f(x)$ 最小化。

过程：得到 $x^{(k)}$ 后，缺定下降方向 $d^{(k)}$ 以及步长 $\alpha$ 实现 $f\left(x^{(k)}+\alpha d^{(k)}\right)$ 最小化。

一般方向为梯度的反方向，步长由泰勒展开得到。

之前学的Newton法解非线性方程 $x_{k+1} = x_k-\dfrac{f(x_k)}{f^{'}(x_{k})}$ ，Newton法解非线性方程组都是一样的思想。

### 黄金分割法（0.618法）
基本原理就是对于单股函数，将区间分为三段并通过比较中间亮点的函数值，可以得到极小值的精细区间，多次迭代即可缩小区间，最终确定位置。

代码[线性搜索算法.cpp](../../Code/线性搜索算法.cpp)中的 `gsm()` 函数实现了一般的黄金分割法

```cpp
double gsm(double (*f)(double), double a, double b)
{
    vector<double> lam = {a + (1 - alpha) * (b - a), a}, mu = {a + alpha * (b - a), b};
    int cnt = 0;
    while(b - a > EPS)
    {
        int k = cnt % 2, kk = (cnt + 1) % 2;
        if(f(lam[k]) > f(mu[k]))
        {
            a = lam[k], lam[kk] = mu[k];
            mu[kk] = a + alpha * (b - a);
        }
        else
        {
            b = mu[k], mu[kk] = lam[k];
            lam[kk] = a + (1 - alpha) * (b - a);
        }
        cnt += 1;
        cout << cnt << " " << a << " " << b << endl;
    }
    return a + alpha * (b - a);
}
```

### Fibonacci

基于斐波那契数列改进黄金分割法

$$\begin{cases}
    \lambda_k = a_k+\dfrac{F_{n-k-1}}{f_{n-k+1}}(b_k-a_k)\\
    \mu_k=a_k+\dfrac{F_{n-k}}{f_{n-k+1}}(b_k-a_k)
\end{cases},k=1,2,\dots,n-1$$

如果 $f(\mu_k)>f(\lambda_k)$ 则令 $b_{k+1}=\mu_k$

如果 $f(\mu_k)<f(\lambda_k)$ 则令 $a_{k+1}=\lambda_k$

注意，其中 $n$ 由 $F_n\geq\dfrac{b_1-a_1}{\varepsilon}$ 确定。

代码[线性搜索算法.cpp](../../Code/线性搜索算法.cpp)中的 `fibonacci()` 函数实现了一般的Fibonacci割法

```cpp
double fibonacci(double (*f)(double), double a, double b)
{
    vector<double> fib(50);
    fib[0] = 1, fib[1] = 1;
    for(int i = 2; i < MAXN; i ++) fib[i] = fib[i - 1] + fib[i - 2];

    double lam, mu;
    int cnt = 1, n;
    for(n = 1; fib[n] <= (b - a) / EPS; n ++){}
    cout << n << endl;
    while (b - a > EPS && cnt < n)
    {
        lam = a + fib[n - cnt - 1] / fib[n - cnt + 1] * (b - a);
        mu = a + fib[n - cnt] / fib[n - cnt + 1] * (b - a);
        if(f(lam) > f(mu)) a = lam;
        else b = mu;
        cout <<cnt << " a=" << a << " b=" << b << endl;
        cnt += 1;
    }
    return a + alpha * (b - a);
}
```

## 排序算法
课堂上的排序算法介绍的很简单，~~但是众所周知，排序算法比的就是你的板子多不多~~

### 冒泡排序
基本思想：每次循环将最大的元素移动至最后。这样的操作一共需要进行 $n$ 次

时间复杂度： $O\left(n^2\right)$

代码[排序算法.cpp](../../Code/排序算法.cpp)中的`bubbleSort()`函数实现了一般的冒泡算法。

```cpp
void bubbleSort(vector<ELEMTYPE>& arr, int left, int right)
{
    for(int i = 0; i <= right - left; i ++)
    {
        for(int j = left; j < right - i; j ++)
        {
            if (arr[j] > arr[j + 1])
            {
                ELEMTYPE tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
```

### 选择排序
基本思想：每次将为排序的最小元素放到已排序元素的最后。

时间复杂度： $O\left(n^2\right)$

其实可以进行一些优化，用一个长度为 $n$ 的数组就可以实现。代码[排序算法.cpp](../../Code/排序算法.cpp)中的`selectSort()`函数实现了一般的选择排序算法。

```cpp
void selectSort(vector<ELEMTYPE>& arr, int left, int right)
{
    for(int i = left; i < right; i ++)
    {
        int minpos = i;
        for(int j = i + 1; j <= right; j ++)
        {
            if(arr[minpos] > arr[j]) minpos = j;
        }
        ELEMTYPE tmp = arr[i];
        arr[i] = arr[minpos];
        arr[minpos] = tmp;
    }
}
```

### 插入排序
基本思想：每次将一个元素按照大小顺序插入到以已排序序列之中。

时间复杂度： $O\left(n^2\right)$

其实实现插入排序的最理想数据结构是链表，但是也只是对时间读作出常数优化，故这里还是使用数组来储存数据。

```cpp
void insertSort(vector<ELEMTYPE>& arr, int left, int right)
{
    for(int i = left + 1; i <= right; i ++)
    {
        int j;
        for(j = left; j < i && arr[j] <= arr[i]; j ++) {}
        ELEMTYPE tmp = arr[i];
        for(int k = i ; k > j; k --) arr[k] = arr[k - 1];
        arr[j] = tmp;
    }
}
```

时间复杂度优化的方向：分部排序，不要想着一次性把所有的都排出来。

### 希尔排序
基本思想：优先比较距离较远的元素。

时间复杂度： $O\left(n\log(n)\right)$

代码[排序算法.cpp](../../Code/排序算法.cpp)中的`shellSort()`函数实现了一般的希尔排序算法。

```cpp
void shellSort(vector<ELEMTYPE>& arr, int left, int right)
{
    int n = right - left + 1;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = left + gap; i <= right; i++)
        {
            ELEMTYPE tmp = arr[i];
            int j;
            for (j = i; j >= left + gap && arr[j - gap] > tmp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = tmp;
        }
    }
}
```

### 归并排序
基本思想：分治，已排序的序列可以快速合成整个排序的序列

时间复杂度： $O\left(n\log(n)\right)$

代码[排序算法.cpp](../../Code/排序算法.cpp)中的`mergeSort()`函数实现了一般的归并排序算法，其中，需要辅助函数`merge()`来实现合并两个已排序数组。

```cpp
void merge(vector<int>& arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        } 
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}
```

### 快速排序
基本思想：找基准，然后以基准分批。

时间复杂度： $O\left(n\log(n)\right)$

y1s1，快速排序拉完了，不是稳定排序切可以摇摆到 $O\left(n^2\right)$ 可能会被卡。直接使用标准库函数即可。

```cpp
sort(f.begin(), f.end());
// 或者使用qsort但是自己手写cmp函数
```

### 堆排序
基本思想：和选择排序类似，但是可以使用优先队列（最小堆）来大大加快找到最小的元素。

时间复杂度： $O\left(n\log(n)\right)$

代码[排序算法.cpp](../../Code/排序算法.cpp)中的`heapSort()`函数利用了标准库容器`priority_queue`实现了一般的堆排序算法。

```cpp
void heapSort(vector<ELEMTYPE>& arr, int left, int right)
{
    priority_queue<ELEMTYPE> pq;
    for (int i = left; i <= right; i++)
    {
        pq.push(arr[i]);
    }
    for (int i = right; i >= left; i--)
    {
        arr[i] = pq.top();
        pq.pop();
    }
}
```

当然你也可以用一维数组手动构建完全二叉树来实现最小堆。代码[排序算法.cpp](../../Code/排序算法.cpp)中就实现了一个最小堆类`MinHeap`来全手动实现堆排序

```cpp
class MinHeap
{
    vector<ELEMTYPE> data;

    void siftUp(int idx)
    {
        while (idx > 0)
        {
            int parent = (idx - 1) / 2;
            if (data[idx] < data[parent])
            {
                swap(data[idx], data[parent]);
                idx = parent;
            }
            else break;
        }
    }

    void siftDown(int idx)
    {
        int n = data.size();
        while (true)
        {
            int smallest = idx;
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            if (left < n && data[left] < data[smallest])
                smallest = left;
            if (right < n && data[right] < data[smallest])
                smallest = right;
            if (smallest != idx)
            {
                swap(data[idx], data[smallest]);
                idx = smallest;
            }
            else break;
        }
    }

public:
    void push(ELEMTYPE val)
    {
        data.push_back(val);
        siftUp(data.size() - 1);
    }

    void pop()
    {
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
    }

    ELEMTYPE top()
    {
        return data[0];
    }

    bool empty()
    {
        return data.empty();
    }
};

void myHeapSort(vector<ELEMTYPE>& arr, int left, int right)
{
    MinHeap mh;
    for (int i = left; i <= right; i++)
        mh.push(arr[i]);
    for (int i = left; i <= right; i++)
    {
        arr[i] = mh.top();
        mh.pop();
    }
}
```