//solves number of components after adding or removing edges
struct ST{
    int n;
    vector<vector<pair<int,int>>>tree;
    vector<int>ans, p, sz;
    stack<tuple<int,int, int, int>>st;
    int comp;
    ST(int _n, int cnt){
        n = _n;
        tree.resize(4*n);
        ans.resize(n+5);
        p.resize(n+5);
        sz.resize(n+5);
        for(int i=0;i<=n;i++)p[i] = i, sz[i] = 1;
        comp = cnt;
    }
    void update(int ind, int l, int r, int ql, int qr, int a, int b){
        if(ql>r or qr<l)return;
        if(l>=ql and r<=qr){
            tree[ind].push_back({a, b});
            return;
        }
        int mid = (l+r)/2;
        update(2*ind, l, mid, ql, qr, a, b);
        update(2*ind+1, mid+1, r, ql, qr, a, b);
    }
    void update(int l, int r, int a, int b)
    {
        update(1, 0, n, l, r, a, b);
    }
 
    int find_set(int ind){
        if(ind==p[ind])return ind;
        return find_set(p[ind]);
    }   
    void merge_set(int ind1, int ind2)
    {
        ind1 = find_set(ind1);
        ind2 = find_set(ind2);
        if(ind1==ind2){
            st.push({-1, -1, -1, -1});
            return;
        }
        if(sz[ind1]<sz[ind2])swap(ind1, ind2);
        st.push({ind1, ind2, sz[ind1], sz[ind2]});
        p[ind2] = ind1;
        sz[ind1] += sz[ind2];
        comp--;
    }
    void rollback(){
        auto [dest, src, sz1, sz2] = st.top();
        st.pop();
        if(dest==-1)return;
        p[src] = src;
        sz[dest] = sz1;
        sz[src] = sz2; 
        comp++;
    }
    void go(int ind, int l, int r)
    {
        for(auto [a, b]: tree[ind]){
            merge_set(a, b);
        }
        if(l==r){
            ans[l] = comp;
        }
        else{
            int mid = (l+r)/2;
            go(2*ind, l, mid);
            go(2*ind+1, mid+1, r);
        }
        for(auto [a, b]: tree[ind])rollback();
    }
 
    void go(){
        go(1, 0, n);
    }
 
};
