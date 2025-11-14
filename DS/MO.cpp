//Make sqrt(n) buckets. Put (L, R) in buckets according to L. Then Sort using R and iterate. R just increases. only need add and rollback. 
struct Query{
  int l, r, id;
  bool operator<(const Query &other) const{
    if(r!=other.r)return r<other.r;
    if(l!=other.l)return l<other.l;
    return id<other.id;
  }
};
struct Bucket{
  int l = -1, r = -1;
  vector<Query>query;
};
struct MO{
  vector<int>v;
  int n;
  stack<tuple<int,int,int>>st;
  int val;
  MO(vector<int>&_v){
    v = _v;
    n = v.size();
    val = 0;
  }
  void add(int ind){
    int x = v[ind];
    st.push({x, -1, val});
    val -= cnt[x]*cnt[x]*x;
    cnt[x]++;
    val += cnt[x]*cnt[x]*x;
  }
  void rollback(){
    auto [x, op, prevval] = st.top();
    st.pop();
    val = prevval;
    cnt[x] += op;
  }
  int cng(int x, int op, int val){
    val -= cnt[x]*cnt[x]*x;
    cnt[x] += op;
    val += cnt[x]*cnt[x]*x;
    return val;
  }
  void brute_force(Query &q){
    int val = 0;
    for(int i=q.l;i<=q.r;i++){
      val = cng(v[i], 1, val);
    }
    ans[q.id] = val;
    for(int i=q.l;i<=q.r;i++){
      cnt[v[i]]--;
    }
  }
  void clr(){
    while(!st.empty()){
      auto [x, op, prevval] = st.top();
      st.pop();
      cnt[x]+=op;
      val = prevval;
    }
  }
  void go(Bucket &b){
    vector<Query>&q = b.query;
    sort(q.begin(), q.end());
    int now = b.r;
    for(auto i: q){
      if(i.r>b.r){
        while(now<i.r){
          add(++now);
        }
        int st = b.r+1;
        while(st>i.l)add(--st);
        ans[i.id] = val;
        while(st<b.r+1){
          rollback();
          st++;
        }
      }
      else{
        brute_force(i);
      }
    }
    clr();
  }
};

void solve()
{
  int n, t;
  cin >> n >> t;
  int bucketcnt = sqrt(n)+5;

  vector<int>v(n+1);

  for(int i=1;i<=n;i++)cin >> v[i];

  int sq = sqrt(n)+1;

  vector<Bucket>b(bucketcnt);
  
  int now = 1, ind = 0;

  vector<int>sts;

  while(now<=n){
    sts.push_back(now);
    b[ind].l = now;
    now += sq;
    b[ind].r = now-1;
    ind++;
  }
  for(int i=0;i<t;i++){
    int l, r;
    cin >> l >> r;

    int tmp = upper_bound(sts.begin(), sts.end(), l) - sts.begin();
    tmp--;

    b[tmp].query.push_back({l, r, i});
  }

  MO mo = MO(v);

  for(int i=0;i<bucketcnt;i++){
    if(b[i].query.size())mo.go(b[i]);
  }

  for(int i=0;i<t;i++)cout << ans[i] << "\n";
}
