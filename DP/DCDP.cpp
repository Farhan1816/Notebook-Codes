//https://codeforces.com/contest/321/problem/E
vector<int>dp, dpo;
int val[N][N];
// int cost[N][N];
void compute(int l, int r, int optl, int optr)
{
    if(l>r)return;
    int mid = (l+r)>>1;
 
    pair<int,int>best = {INF, -1};
 
    for(int i=optl;i<=min(mid, optr);i++)
    {
        best = min(best, {dpo[i-1]  + val[mid][mid] - val[i-1][mid] - val[mid][i-1] + val[i-1][i-1], i});
    }
 
    dp[mid] = best.first;
    int opt = best.second;
 
    compute(l, mid-1, optl, opt);
    compute(mid+1, r, opt, optr);
}
void solve()
{
    int n, k;
    cin  >> n >> k;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
        getchar();
        val[i][j] = getchar() - '0';
        val[i][j] += val[i-1][j] + val[i][j-1] - val[i-1][j-1];
    }
    dpo.assign(n+1, INF);
    dp.assign(n+1, INF);
    dpo[0] = 0;
    dp[0] = 0;
    for(int i=1;i<=k;i++)
    {
        compute(1, n, 1, n);
        dpo = dp;
    }
    printf("%d", (dp[n]>>1));
}
