vector<vector<int>>aut(N, vector<int>(26));
vector<int>pi(N);

vector<vector<pair<int,int>>>adj(N);

int dfs(int ind, string &s, int len = 0){
    int sz = s.size();
    int ret = 0;
    if(s.size()==0){
        for(auto i: adj[ind]){
            s.push_back(i.second);
            ret = max(ret, dfs(i.first, s, len+1));
            s.pop_back();
        }
    }
    else if(sz==1){
        aut[0][s.back()-'a'] = sz;
        for(auto i: adj[ind]){
            s.push_back(i.second);
            ret = max(ret, dfs(i.first, s, len+1));
            s.pop_back();
        }
        aut[0][s.back()-'a'] = 0;
    }
    else{
        for(int i=0;i<26;i++)aut[sz-1][i] = aut[pi[sz-2]][i];
        aut[sz-1][s.back()-'a'] = sz;
        int j = pi[sz-2];
        pi[sz-1] = aut[j][s.back()-'a'];

        for(auto i: adj[ind]){
            s.push_back(i.second);
            ret = max(ret, dfs(i.first, s, len+1));
            s.pop_back();
        }
        aut[sz-1][s.back()-'a'] = aut[pi[sz-2]][s.back()-'a'];
    }

    if(sz-1>=0 and pi[sz-1]!=0 and len!=0 and (len%(len-pi[sz-1])==0)){
        ret = max(ret, len - pi[sz-1]);
    }
    return ret;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>v(n);
    for(int i=0;i<n-1;i++){
        cin >> v[i];
    }
    string s;
    cin >> s;
    pi[0] = 0;
    for(int i=0;i<n-1;i++){
        adj[v[i]].push_back({i+2, s[i]});
    }
    s.clear();
    cout << dfs(1, s) << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    for(int i=1;i<=t;i++){
        solve();
    }
}
