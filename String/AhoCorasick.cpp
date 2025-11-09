struct AC {
  int N, P;
  const int A = 26;
  vector <vector <int>> next;
  vector <int> link, out_link;
  vector <vector <int>> out;
  vector<int>cnt;
  
  AC(): N(0), P(0) {node();}
  
  int node() {
    next.emplace_back(A, 0);
    link.emplace_back(0);
    out_link.emplace_back(0);
    out.emplace_back(0);
    return N++;
  }

  inline int get (char c) {
    return c - 'a';
  }

  int add_pattern (const string T) {
    int u = 0;
    for (auto c : T) {
      if (!next[u][get(c)]) next[u][get(c)] = node();
      u = next[u][get(c)];
    }
    out[u].push_back(P);
    return P++;
  }

  void compute() {
    cnt.resize(N);
    queue <int> q;
    for (q.push(0); !q.empty();) {
      int u = q.front(); q.pop();
      for (int c = 0; c < A; ++c) {
        int v = next[u][c];
        if (!v) next[u][c] = next[link[u]][c];
        else {
          link[v] = u ? next[link[u]][c] : 0;
          out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
          q.push(v);
        }
      }
    }
}

  int advance (int u, char c) {
    while (u && !next[u][get(c)]) u = link[u];
    u = next[u][get(c)];
    return u;
  }

  vector<int>go(string &s) // count for each pattern the number of positions where it appears in s.
  {
    vector<int>ans(P);
    vector<int>tmpans(N);
    int now = 0;
    for(auto i: s){
        now = advance(now, i);
        cnt[now]++;
    }
    
    for(int i=0;i<N;i++){
        for(int j=i;j;j=out_link[j]){
            tmpans[j]+=cnt[i];
        }
    }

    for(int i=0;i<N;i++){
        for(auto j: out[i])ans[j] += tmpans[i];
    }
    return ans;
  }

  void match (const string S) {
    int u = 0;
    for (auto c : S) {
      u = advance(u, c);
      for (int v = u; v; v = out_link[v]) {
        for (auto p : out[v]) cout << "match " << p << endl;
      }
    }
  }
};
