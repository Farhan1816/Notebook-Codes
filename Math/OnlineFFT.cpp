//DC part of Jetpack. Works even if both dps depend on each other. 
void go(int l, int r)
{
    if (l == r)
    {
        if (l != 1)
        {
            bit.add(l, cat[l]);
        }
        dp[l] = bit.sum(0, l);
        return;
    }
    int mid = (l + r) / 2;
    go(l, mid);
    vector<int> a, b;
    for (int i = l; i <= mid; i++)
        a.push_back(dp[i]);
    for (int j = 0; j <= min(r - l + 1, mid); j++)
        b.push_back(cat[j]);
    vector<int> tmp = multiplyMod(a, b);
    for (int i = 0; i < tmp.size(); i++)
    {
        int pos = l + i;
        if (pos > mid and pos <= r)
        {
            bit.add(pos, tmp[i]);
        }
    }
    a.clear();
    b.clear();
    for (int i = l; i <= mid; i++)
        a.push_back(cat[i]);
    for (int j = 0; j <= min(l - 1, r - l + 1); j++)
        b.push_back(dp[j]);
    tmp = multiplyMod(a, b);
    for (int i = 0; i < tmp.size(); i++)
    {
        int pos = l + i;
        if (pos > mid and pos <= r)
        {
            bit.add(pos, tmp[i]);
        }
    }
    go(mid + 1, r);
}

