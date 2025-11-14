//Solves https://codeforces.com/contest/342/problem/E
vector<vector<int>>adj(N);
vector<vector<pair<int,int>>>anc(N);
int n, k;
vector<int>v, v2;
bool removed[N];
int sz[N];
int cnt[M];
int ans[N];
int get_size(int ind, int p=-1)
{
  sz[ind] = 1;
  for(auto x: adj[ind])
  {
    if(x!=p and !removed[x])
    {
      sz[ind]+=get_size(x, ind);
    }
  }
  return sz[ind];
}
int get_cent(int ind, int tot_size, int p = -1)
{
  for(auto x: adj[ind])
  {
    if(x!=p and !removed[x] and 2*sz[x]>tot_size)
    {
        return get_cent(x, tot_size, ind);
    }
  }
  return ind;
}
void dfs(int ind,  int root, int p=-1, int d=0)
{
  anc[ind].push_back({root, d});
  for(auto i: adj[ind])
  {
    if(i!=p and !removed[i])dfs(i, root, ind, d+1);
  }
}
void go(int ind = 1, int p = -1)
{
  int cent = get_cent(ind, get_size(ind));
  dfs(cent, cent);
  removed[cent] = 1;
  for(auto x: adj[cent])
  {
    if(!removed[x])
    {
      go(x);
    }
  }
}
void prop(int ind)
{
  for(auto [x, y]: anc[ind])
  {
    ans[x] = min(ans[x], y);
  }
}
int find_ans(int ind)
{
  int ret = INF;
  for(auto [x, y]: anc[ind])
  {
    ret = min(ret, y+ans[x]);
  }
  return ret;
}
void solve()
{ 
  int n, m;
  cin >> n >> m;
  for(int i=0;i<n-1;i++)
  {
    int x, y;
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  go();
  for(int i=2;i<=n;i++)ans[i] = INF;
  prop(1);
  while(m--)
  {
    int t, v;
    cin >> t >> v;
    if(t==1)
    {
      prop(v);
    }
    else{
      cout << find_ans(v) << "\n";
    }
  }
}
