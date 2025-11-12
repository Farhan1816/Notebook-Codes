struct edge {
  int u, v;
  ll cap, flow;
  edge () {}
  edge (int u, int v, ll cap) : u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
  int N;
  vector <edge> E;
  vector <vector <int>> g;
  vector <int> d, pt;
  
  Dinic (int N) : N(N), E(0), g(N), d(N), pt(N) {}

  void AddEdge (int u, int v, ll cap) {
    if (u ^ v) {
      E.emplace_back(u, v, cap);
      g[u].emplace_back(E.size() - 1);
      E.emplace_back(v, u, 0);
      g[v].emplace_back(E.size() - 1);
    }
  }

  bool BFS (int S, int T) {
    queue <int> q({S});
    fill(d.begin(), d.end(), N + 1);
    d[S] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == T) break;
      for (int k : g[u]) {
        edge &e = E[k];
        if (e.flow < e.cap and d[e.v] > d[e.u] + 1) {
          d[e.v] = d[e.u] + 1;
          q.emplace(e.v);
        }
      }
    } return d[T] != N + 1;
  }

  ll DFS (int u, int T, ll flow = -1) {
    if (u == T or flow == 0) return flow;
    for (int &i = pt[u]; i < g[u].size(); ++i) {
      edge &e = E[g[u][i]];
      edge &oe = E[g[u][i] ^ 1];
      if (d[e.v] == d[e.u] + 1) {
        ll amt = e.cap - e.flow;
        if (flow != -1 and amt > flow) amt = flow;
        if (ll pushed = DFS(e.v, T, amt)) {
          e.flow += pushed;
          oe.flow -= pushed;
          return pushed;
        }
      }
    } return 0;
  }

  ll MaxFlow (int S, int T) {
    ll total = 0;
    while (BFS(S, T)) {
      fill(pt.begin(), pt.end(), 0);
      while (ll flow = DFS(S, T)) total += flow;
    }
    return total;
  }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    int add = n;

    Dinic dinic = Dinic(n+m+2);

    int source = 0, sink = n+m+1;

    vector<vector<int>>adj(n+1);

    vector<vector<bool>>ase(n+1, vector<bool>(m+1));

    for(int i=0;i<k;i++){
        int x, y;
        cin >> x >> y;
        ase[x][y] = 1;
        y+=n;
        dinic.AddEdge(x, y, 1);
        adj[x].push_back(y);
    }

    for(int i=1;i<=n;i++)dinic.AddEdge(0, i, 1);
    for(int i=n+1;i<=n+m;i++)dinic.AddEdge(i, n+m+1, 1);

    cout << dinic.MaxFlow(source, sink) << "\n";

    for(int i=1;i<=n;i++){
        for(auto id: dinic.g[i]){
            auto &e = dinic.E[id];
            if(e.v>n and e.v<=n+m and e.flow>0)cout << e.u << " " << e.v-n << "\n";
        }
    }
}
