//0-indexed
//https://cses.fi/problemset/task/1696/
struct HopcroftKarp
{
    int n, m;
    vector<int> l, r, lv, ptr;
    vector<vector<int>> adj;
    HopcroftKarp() {}
    HopcroftKarp(int _n, int _m) { init(_n, _m); }
    void init(int _n, int _m)
    {
        n = _n, m = _m;
        adj.assign(n + m, vector<int>{});
    }
    void addEdge(int u, int v)
    {
        adj[u].emplace_back(v + n);
    }
    void bfs()
    {
        lv = vector<int>(n, -1);
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (l[i] == -1)
            {
                lv[i] = 0;
                q.emplace(i);
            }
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adj[u])
                if (r[v] != -1 && lv[r[v]] == -1)
                {
                    lv[r[v]] = lv[u] + 1;
                    q.emplace(r[v]);
                }
        }
    }
    bool dfs(int u)
    {
        for (int &i = ptr[u]; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (r[v] == -1 || (lv[r[v]] == lv[u] + 1 && dfs(r[v])))
            {
                l[u] = v, r[v] = u;
                return true;
            }
        }
        return false;
    }
    int maxMatching()
    {
        int match = 0, cnt = 0;
        l = r = vector<int>(n + m, -1);
        do
        {
            ptr = vector<int>(n);
            bfs();
            cnt = 0;
            for (int i = 0; i < n; i++)
                if (l[i] == -1 && dfs(i))
                    cnt++;
            match += cnt;
        } while (cnt);
        return match;
    }
    void printMatching()
    {
        for (int i = 0; i < n; ++i)
        {
            if (l[i] != -1)
            {
                cout << i+1 << " " << l[i] - n + 1 << "\n";
            }
        }
    }
};
void solve()
{
  int n, m, k;
  cin >> n >> m >> k;
  HopcroftKarp hk(n, m);
  for(int i=0;i<k;i++){
    int x, y;
    cin >> x >> y;
    x--, y--;
    hk.addEdge(x, y);
  }
  cout << hk.maxMatching() << "\n";
  hk.printMatching();
}
