#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef int ELEMTYPE; // 在这里快速切换需要排序的元素类型
/*
所有的函数都有三个参数：
arr: 需要排序的数组
left: 排序的起点（包含）
right: 排序的终点（包含）
*/

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

int main()
{
    vector<ELEMTYPE> a = {5, 2, 8, 1, 9};
    vector<ELEMTYPE> b = {5, 2, 8, 1, 9};
    vector<ELEMTYPE> c = {5, 2, 8, 1, 9};
    vector<ELEMTYPE> d = {5, 2, 8, 1, 9};
    vector<ELEMTYPE> e = {5, 2, 8, 1, 9};
    vector<ELEMTYPE> f = {5, 2, 8, 1, 9};
    vector<ELEMTYPE> g = {5, 2, 8, 1, 9};

    int left = 0;
    int right = a.size() - 1;

    cout << "bubbleSort:    ";
    bubbleSort(a, left, right);
    for (int i = 0; i <= right; i++) cout << a[i] << " ";
    cout << endl;

    cout << "selectSort:    ";
    selectSort(b, left, right);
    for (int i = 0; i <= right; i++) cout << b[i] << " ";
    cout << endl;

    cout << "insertSort:    ";
    insertSort(c, left, right);
    for (int i = 0; i <= right; i++) cout << c[i] << " ";
    cout << endl;

    cout << "shellSort:     ";
    shellSort(d, left, right);
    for (int i = 0; i <= right; i++) cout << d[i] << " ";
    cout << endl;

    cout << "heapSort(STL): ";
    heapSort(e, left, right);
    for (int i = 0; i <= right; i++) cout << e[i] << " ";
    cout << endl;

    cout << "Qsort:         ";
    sort(f.begin(), f.end());
    for (int i = 0; i <= right; i++) cout << f[i] << " ";
    cout << endl;

    cout << "heapSortManual:";
    myHeapSort(g, left, right);
    for (int i = 0; i <= right; i++) cout << g[i] << " ";
    cout << endl;

    return 0;
}