#include <iostream>
#include <vector>
using namespace std;

// 你只需要在这里按照用数组存储二叉树的规则修改数组即可
vector<char> tree={'A', 'B', 'E', 'C',
'D', '\0', 'F', '\0', 'G', 'H', '\0'};

void firstOrder(int node, int n)
{
    int lk = 2 * node + 1, rk = 2 * node + 2;
    cout << tree[node] << " ";
    if (lk < n && tree[lk] != '\0') firstOrder(lk, n);
    if (rk < n && tree[rk] != '\0') firstOrder(rk, n);
}

void middleOrder(int node, int n)
{
    int lk = 2 * node + 1, rk = 2 * node + 2;
    if (lk < n && tree[lk] != '\0') middleOrder(lk, n);
    cout << tree[node] << " ";
    if (rk < n && tree[rk] != '\0') middleOrder(rk, n);
}

void lastOrder(int node, int n)
{
    int lk = 2 * node + 1, rk = 2 * node + 2;
    if(lk < n && tree[lk] != 0) lastOrder(lk, n);
    if(rk < n && tree[rk] != 0) lastOrder(rk, n);
    cout << tree[node] << " ";
}

int main()
{
    firstOrder(0, tree.size());
    cout << "\n";
    middleOrder(0, tree.size());
    cout << "\n";
    lastOrder(0, tree.size());
    cout << "\n";
}