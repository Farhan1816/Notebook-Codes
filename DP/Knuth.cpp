inline int cost(int l, int r)
{
    return val[r] - (l > 0 ? val[l - 1] : 0);
}
 
void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> val[i];
 
    // prefix sum for O(1) range cost
    for (int i = 1; i < n; i++)
        val[i] += val[i - 1];
 
    // base cases: single element segments have cost 0, opt is l
    for (int i = 0; i < n; i++)
    {
        saved[i][i] = 0;
        opt[i][i] = i;
    }
 
    // increasing segment length
    for (int len = 2; len <= n; len++)
    {
        for (int l = 0; l + len - 1 < n; l++)
        {
            int r = l + len - 1;
            int start = opt[l][r - 1];
            int end = opt[l + 1][r];
            if (end > r - 1)
                end = r - 1;
 
            pair<int, int> best = {INF, -1};
            for (int i = start; i <= end; i++)
            {
                int cur = cost(l, r) + saved[l][i] + saved[i + 1][r];
                if (cur < best.first)
                {
                    best = {cur, i};
                }
            }
            saved[l][r] = best.first;
            opt[l][r] = best.second;
        }
    }
 
    cout << saved[0][n - 1] << "\n";
}
