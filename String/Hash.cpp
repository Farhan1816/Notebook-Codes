struct Hash{
    string s;
    vector<pair<ll, ll>> hashval;
    vector<pair<ll, ll>> power;
    int n;
    ll base1, base2, M1, M2;

    Hash(string _s){
        n = (int)_s.size();
        s = _s;
        hashval.resize(n);
        power.resize(max(1, n));
        base1 = 31; base2 = 37;
        M1 = 1000000007LL; M2 = 1000000013LL;
        build();
    }

    void build(){
        power[0] = {1, 1};
        for(int i = 1; i < n; ++i){
            power[i].first  = (power[i-1].first * base1) % M1;
            power[i].second = (power[i-1].second * base2) % M2;
        }
        for(int i=0;i<n;i++){
            int c = s[i]-'a' + 1;
            if(i==0) hashval[i] = {c % M1, c % M2};
            else{
                hashval[i].first  = (hashval[i-1].first * base1 + c) % M1;
                hashval[i].second = (hashval[i-1].second * base2 + c) % M2;
            }
        }
    }

    pair<ll,ll> range_hash(int l, int r){
        if(l < 0) l = 0;
        if(r >= n) r = n-1;
        if(l > r) return {0,0};
        if(l == 0) return hashval[r];
        ll x = (hashval[r].first - (hashval[l-1].first * power[r-l+1].first) % M1) % M1;
        if(x < 0) x += M1;
        ll y = (hashval[r].second - (hashval[l-1].second * power[r-l+1].second) % M2) % M2;
        if(y < 0) y += M2;
        return {x, y};
    }
};
