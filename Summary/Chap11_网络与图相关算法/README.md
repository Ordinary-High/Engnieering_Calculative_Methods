## 知识点总结
本节课对应的[PPT](../../PPT/第11章%20网络与图相关算法(2026).pdf)
本节课对应的[代码1](../../Code/树的遍历算法.cpp)，[代码2](../../Code/图的遍历与最短路径.cpp)

快速索引
- [知识点总结](#知识点总结)
- [树的遍历算法](#树的遍历算法)
  - [二叉树的存储](#二叉树的存储)
  - [前序、中序、后序遍历方法](#前序中序后序遍历方法)
  - [前序、中序、后序的转换与反推二叉树](#前序中序后序的转换与反推二叉树)
- [图的遍历算法](#图的遍历算法)
  - [图的存储](#图的存储)
    - [邻接矩阵](#邻接矩阵)
    - [邻接表](#邻接表)
  - [深度优先搜索算法](#深度优先搜索算法)
  - [广度优先搜索算法](#广度优先搜索算法)
- [最短路径](#最短路径)
  - [Dijkstra算法](#dijkstra算法)
  - [Floyd算法](#floyd算法)

## 树的遍历算法
其实树可以很复杂，但是我们课上讨论二叉树是重点。

一般的完全二叉树如下
<p align="center">
  <img src="assets/complete_binary_tree.drawio.svg" alt="完全二叉树", width="80%"/>
</p>

基于此我们展开讨论。

### 二叉树的存储
作者非常推荐用数组来存储二叉树。我们将二叉树的每个节点从 $0$ 开始编号，每一层的节点从左到右编号一次编号。

则我们开一发现，对于编号为 $i$ 的节点其左右叶子节点分别为

$$left = 2 \times i + 1, \space right = 2 \times i + 2$$

根节点为

$$p =  \left \lfloor \dfrac{i}{2}\right \rfloor$$

我们可以方便的和快速读取一棵树。

对于比较稀疏的二叉树，数组会有很大的空间浪费，我们也可以用结构体加指针的方式来存储二叉树

```c
typedef struct _node
{
    int ind;
    struct _node *left, *right;
}Node, *Nodeprt;
```

### 前序、中序、后序遍历方法

这里的遍历方法都是**先访问左叶子节点，在访问右叶子节点**。关键就是根节点在之前、之中还是之后。这其中的算法都可以用递归函数来快速地实现。

**前序算法：** `根节点->左叶子节点->右叶子节点`
```cpp
void firstOrder(int node, int n)
{
    int lk = 2 * node + 1, rk = 2 * node + 2;
    cout << tree[node] << " ";
    if (lk < n && tree[lk] != '\0') firstOrder(lk, n);
    if (rk < n && tree[rk] != '\0') firstOrder(rk, n);
}
```

**中序算法：** `左叶子节点->根节点->右叶子节点`
```cpp
void middleOrder(int node, int n)
{
    int lk = 2 * node + 1, rk = 2 * node + 2;
    if (lk < n && tree[lk] != '\0') middleOrder(lk, n);
    cout << tree[node] << " ";
    if (rk < n && tree[rk] != '\0') middleOrder(rk, n);
}
```

**后序算法：** `左叶子节点->右叶子节点->根节点`
```cpp
void lastOrder(int node, int n)
{
    int lk = 2 * node + 1, rk = 2 * node + 2;
    if(lk < n && tree[lk] != 0) lastOrder(lk, n);
    if(rk < n && tree[rk] != 0) lastOrder(rk, n);
    cout << tree[node] << " ";
}
```

### 前序、中序、后序的转换与反推二叉树
~~根据老师布置的作业，作者猜测这块应该会出理论考试题目~~

要解决这个问题的关键思想就是分治以及熟练使用前序、中序、后序的性质

- **分治：** 可以发现，任何一个前序序列都是 `根节点+左子树前序序列+右子树前序序列` ，因此我们需要做的就是分别确定根节点、左子树前序序列以及右子树序列，然后进行相同的分治操作，直至一个子树仅剩小于 $3$ 个节点，再进行遍历讨论即可。中序后序序列也是相同的操作
- **不同序列的性质**
  1. 前序序列：第一个节点即为根节点
  2. 中序序列：第一个节点两侧分别为左子树中序序列，右子树中序序列
  3. 后序序列：最后一个节点为根节点

一般情况下需要至少两种序列才能确定一个二叉树
1. **前序序列+中序序列/中序序列+后序序列：** 直接根据前序和后序序列确定根节点，然后用中序序列分开左右两个子树，然后对左右子树进行相同的操作。
2. **前序序列+后序序列：** 枚举左子树的节点个数 $k$ ，检查是否能够实现前序列的前 $k$ 个节点亦是后序序列的前 $k$ 个节点。~~（作者只想到这种方法，有更好的方法欢迎提出来）~~

**例子：**
中序序列 `D E B A F C G` ，后序序列 `E D B F G C A`
1. 确定根节点为 `A` ，左子树的中序序列 `D E B` 、后序序列 `E D B` ；右子树的中序序列 `F C G` 、后序序列 `F G C`
2. 可以知道左子树的根节点为 `B` 右子树的根节点为 `C`
3. 再次细分所有的子树的节点树均小于 $3$ ，故可以通过遍历的方法确定最后的二叉树结果

<p align="center">
  <img src="assets/二叉树序列转换与反推.drawio.svg" alt="完全二叉树", width="100%"/>
</p>

## 图的遍历算法
### 图的存储
一般的图由 $n$ 个节点和 $m$ 条连接节点的边组成，其中节点包含着节点编号等信息，边应该包含距离等信息（边权）。

注意图分为有权图和无权图，分别表示每条边的长度不同和相同。

注意图分为有向图和无向图，分别表示两个节点间的往返的距离相同和不同。

#### 邻接矩阵
用一个 $n\times n$ 的矩阵 $a$ 来储存图的信息，其中 $a_{ij}$ 表示从 $i$ 节点到 $j$ 节点的距离

#### 邻接表
用一个二维数组来记录每个每个节点可以到达的节点以及其距离。

这里以 $\text{C++}$ 为例，图的读取和存储方式为

```cpp
int n, m, u, v, w;
cin >> n >> m;
vector<vector<pair<int, int>>> g(n + 1); // 邻接表
vector<vector<int>> dism(n + 1, vector<int>(n + 1, INF)); // 邻接矩阵
for(int i = 0; i < m; i ++)
{
    fin >> u >> v >> w;
    g[u].push_back({w, v});
    dism[u][v] = w;
}
for(int i = 0; i <= n; i ++) dism[i][i] = 0;
```

### 深度优先搜索算法
一条路走到黑，无路可走就回头另找路，可以用栈先进后出的性质来实现。

代码[图的遍历与最短路径.cpp](../../Code/图的遍历与最短路径.cpp)中的`dfs()` 函数给出了一般的深度优先搜索算法的实现

```cpp
void dfs(int fa, int now, vector<vector<pair<int, int>>> &graph, vector<bool> &vis)
{
    cout << now << ' ';
    vis[now] = true;
    for(auto [w, v] : graph[now])
    {
        if(v != fa && !vis[v]) dfs(now, v, graph, vis); 
    }
}
```

### 广度优先搜索算法
首先探索当前所有可以走的点，然后再往更深一层的探索，可以利用队列先进先出的性质实现

> Be water, my friend.

代码[图的遍历与最短路径.cpp](../../Code/图的遍历与最短路径.cpp)中的`bfs()` 函数给出了一般的广度优先搜索算法的实现

```cpp
void bfs(int s, int n, vector<vector<pair<int, int>>> &graph)
{
    vector<bool> vis(n + 1, false);
    queue<int> qu;

    qu.push(s);
    vis[s] = true;
    while(!qu.empty())
    {
        int u = qu.front();
        cout << u << " ";
        qu.pop();

        for(auto [w, v]: graph[u])
        {
            if(!vis[v])
            {
                vis[v] = true;
                qu.push(v);
            }
        }
    }
}
```

## 最短路径

### Dijkstra算法
核心思想：当前到起点距离最近的点，一定已经找到最短路径

核心操作：用优先队列实现以 $O\lg(n)$ 的时间复杂度找到目前到起点距离最短的点。

代码[图的遍历与最短路径.cpp](../../Code/图的遍历与最短路径.cpp)中的`dijkstra()` 函数给出了一般的Dijkstra算法的实现
```cpp
vector<int> dijkstra(int n, int s, vector<vector<pair<int, int>>> &graph)
{
    vector<int> dis(n + 1, INF);
    priority_queue<P, vector<P>, greater<P>> pq;
    
    pq.push({0, s});
    dis[s] = 0;
    while(!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dis[u]) continue;
        dis[u] = d;

        for(auto [w, v]: graph[u])
        {
            if (d + w < dis[v])
            {
                dis[v] = d + w;
                pq.push({dis[v], v});
            }
        }
    }
    return dis;
}
```

### Floyd算法
核心思想：两个点之间的最短路径一定是路径中一点到两个端点的最短路径的拼接。

核心操作：三层循环去遍历所有的中间点组合，找到最小的。

代码[图的遍历与最短路径.cpp](../../Code/图的遍历与最短路径.cpp)中的`floyd()` 函数给出了一般的Floyd算法的实现

```cpp
void floyd(vector<vector<int>> &graph, int n)
{
    for(int k = 1; k <= n; k ++)
    {
        for(int i = 1; i <= n; i ++)
        {
            for(int j = 1; j <= n; j ++) 
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
        }
    }
}
```
