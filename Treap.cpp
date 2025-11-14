struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
	Node(int val) : val(val), y(rand()) {}
	void recalc();
};
int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() { c = cnt(l) + cnt(r) + 1; }
template<class F> void each(Node* n, F f) {
	if (n) { each(n->l, f); f(n->val); each(n->r, f); }
}
pair<Node*, Node*> split(Node* n, int k) {
	if (!n) return {};
	if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
		auto [L,R] = split(n->l, k);
		n->l = R;
		n->recalc();
		return {L, n};
	} else {
		auto [L,R] = split(n->r,k - cnt(n->l) - 1); // and just "k"
		n->r = L;
		n->recalc();
		return {n, R};
	}
}
Node* merge(Node* l, Node* r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		return l->recalc(), l;
	} else {
		r->l = merge(l, r->l);
		return r->recalc(), r;
	}
}
Node* ins(Node* t, Node* n, int pos) {
	auto [l,r] = split(t, pos);
	return merge(merge(l, n), r);
}
// Example application: move the range [l, r) to index k
void move(Node*& t, int l, int r, int k) {
	Node *a, *b, *c;
	tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
	if (k <= l) t = merge(ins(a, b, k), c);
	else t = merge(a, ins(c, b, k - r));
}
int kth(Node* t, int k)
{
  if(cnt(t->l)>=k)return kth(t->l, k);
  else if(cnt(t->l)==k-1)return t->val;
  else return kth(t->r, k-(cnt(t->l)+1));  
}
void solve()
{
  int n;
  cin >> n; 
  Node* t = NULL;
  for(int i=1;i<=n;i++){
    t = merge(t, new Node(i));
  }
  for(int i=0;i<n;i++){
    int a, b;
    cin >> a >> b;
    if(a>=b)continue;
    a--, b--;
    int sz1 = (b-a);
    int sz2 = (n-b);
    if(sz1<sz2){
 
      auto [L1, R1] = split(t, a);
      auto [L2, R2] = split(R1, sz1);
      auto [L3, R3] = split(R2, sz1);
 
      t = merge(L1, merge(L3, merge(L2, R3)));
    }
    else if(sz2<sz1){
      auto [L1, R1] = split(t, a);
      auto [L2, R2] = split(R1, sz2);
      auto [L3, R3] = split(R2, b-(a+sz2-1)-1);
 
      t = merge(L1, merge(R3, merge(L3, L2)));
    }
    else{
      auto [L1, R1] = split(t, a);
      auto [L2, R2] = split(R1, sz1);
      t = merge(L1, merge(R2, L2));
    }
  }
  for(int i=0;i<n;i++)cout << kth(t, i+1) << " ";
  cout << "\n";
}
