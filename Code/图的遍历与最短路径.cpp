/*
该文件比较特殊，由于图的输入不适合直接在代码中写出来，所以推荐使用输入的方式
输入规则:
第 1 行 2 个整数 n, m，分别代表图的节点数和边数
接下来 m 行，每行表示一条边，包含三个整数 u, v, w。
表示从编号为 u 的节点到编号为 v 的节点的边权为 w
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
using P = pair<int, int>;
#define INF 0x3f3f3f3f

void dfs(int fa, int now, vector<vector<pair<int, int>>> &graph, vector<bool> &vis)
{
    cout << now << ' ';
    vis[now] = true;
    for(auto [w, v] : graph[now])
    {
        if(v != fa && !vis[v]) dfs(now, v, graph, vis); 
    }
}

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

int main()
{
    int n, m, u, v, w;
    ifstream fin("sample_graph.txt"); // 将这里替换为你真实的输入数据路径
    fin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    vector<vector<int>> dism(n + 1, vector<int>(n + 1, INF));
    for(int i = 0; i < m; i ++)
    {
        fin >> u >> v >> w;
        g[u].push_back({w, v});
        dism[u][v] = w;
    }
    for(int i = 0; i <= n; i ++) dism[i][i] = 0;
    fin.close();

    vector<bool> vis(n + 1, false);
    dfs(0, 1, g, vis);
    cout << '\n';
    bfs(1, n, g);
    cout << '\n' << endl;

    vector<int> ans = dijkstra(n, 1, g);
    for(auto x: ans) cout << x << ' ';
    cout << '\n' << endl;

    
    floyd(dism, n);
    for(int i = 1; i <= n; i ++)
    {
        for(int j = 1; j <= n; j ++)
        {
            cout << dism[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}