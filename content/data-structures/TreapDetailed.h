/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
// given a string s, perform m operations of the form:
// 1. reverse the substring s[l..r] (1-indexed)
// 2. move the substring s[l..r] to the end of the string

struct Node {
    Node *l = 0, *r = 0;
    char val;  // if it was a string
    int y, c = 1;
    bool rev = false; 
    int sum, add = 0;      
	bool has_add = 0; 
    Node(char val) : val(val), sum(val-'a'), y(rand()) {}
    void recalc();
};
int cnt(Node* n) { return n ? n->c : 0; }
void Node::recalc() {
    c = 1 + cnt(l) + cnt(r);
	sum = val-'a';
	if (l) sum += l->sum;
	if (r) sum += r->sum;
}
void push(Node* n) {   // push the reverse flag down
    if (!n) return;
    if (n->rev) {
        swap(n->l, n->r); // reverse children
        if (n->l) n->l->rev ^= true;
        if (n->r) n->r->rev ^= true;
        n->rev = false;
    }
    if (n->has_add) {
        n->val += n->add; 
        n->sum += n->add * cnt(n);
        n->has_add = false;
        n->add = 0;
        if(n->l) n->l->has_add = true, n->l->add += n->add;
        if(n->r) n->r->has_add = true, n->r->add += n->add;
    }
}
pair<Node*, Node*> split(Node* n, int k) {  // Split the tree into two parts: the first part contains the first k nodes
    if (!n) return {};
    push(n); 
    if (cnt(n->l) >= k) {
        auto [L, R] = split(n->l, k);
        n->l = R;
        n->recalc();
        return {L, n};
    } else {
        auto [L, R] = split(n->r, k - cnt(n->l) - 1);
        n->r = L;
        n->recalc();
        return {n, R};
    }
}
Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    push(l); 
    push(r); 
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        l->recalc();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->recalc();
        return r;
    }
}
Node* ins(Node* t, Node* n, int pos) {  //insert n at position pos, 0-indexed
    auto [l, r] = split(t, pos);
    return merge(merge(l, n), r);
}
Node* erase(Node* t, int pos) {  //erase at pos, 0 indexed
	Node *a, *b, *c;
	tie(a, b) = split(t, pos);
	tie(b, c) = split(b, 1);
	delete b; // free memory if needed
	return merge(a, c);
}
void move(Node*& t, int l, int r, int k) {  // Example application: move the range [l, r) to index k
    Node *a, *b, *c;
    tie(a, b) = split(t, l);
    tie(b, c) = split(b, r - l);
    if (k <= l) t = merge(ins(a, b, k), c);
    else t = merge(a, ins(c, b, k - r));
}
// get range sum of [l, r)
int range_sum(Node*& t, int l, int r) {
	Node *a, *b, *c;
	tie(a, b) = split(t, l);
	tie(b, c) = split(b, r - l);
	int res = b->sum;
	t = merge(a, merge(b, c));
	return res;
}
// range add [l, r) by x
// if(b) b->add += x, b->has_add = true;
// merge back to t

// range reverse [l, r)
// if(b) b->rev ^= true;
// merge back to t

void each(Node* n, string& out) {
    if (!n) return;
    push(n); 
    each(n->l, out);
    out += n->val;
    each(n->r, out);
}
int main() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    Node* treap = nullptr;
    for (char ch : s) treap = merge(treap, new Node(ch));

    while (m--) {
        int a, b; cin >> a >> b;
        Node *left, *mid, *right;
        tie(left, mid) = split(treap, a - 1);
        tie(mid, right) = split(mid, b - a + 1);
        treap = merge(left, right);
        mid->rev ^= true;   
        treap = merge(treap, mid); // move to end
    }
    string res;
    each(treap, res);  // print the array
    cout << res << '\n';
}
