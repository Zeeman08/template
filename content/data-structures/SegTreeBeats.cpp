class SegtreeBeats {
  vector<ll> sum, mx, smx, mx_c;
  int n;
  void merge(int tv) {
    int l = tv*2, r = tv*2 + 1;
    if(mx[l] < mx[r]) {
      mx[tv] = mx[r], mx_c[tv] = mx_c[r];
      smx[tv] = max(mx[l], max(smx[l], smx[r]));
    }
    else if(mx[l] > mx[r]) {
      mx[tv] = mx[l], mx_c[tv] = mx_c[l];
      smx[tv] = max(mx[r], max(smx[l], smx[r]));
    }
    else {
      mx[tv] = mx[l], mx_c[tv] = mx_c[l] + mx_c[r];
      smx[tv] = max(smx[l], smx[r]);
    }
    sum[tv] = sum[tv*2] + sum[tv*2 + 1];
  }
  void build(int tv, int tl, int tr, vector<ll> &v) {
    if(tl == tr) {
      sum[tv] = mx[tv] = v[tl-1];
      smx[tv] = -inf;
      mx_c[tv] = 1;
    }
    else {
      int tm = (tl + tr) >> 1;
      build(tv*2, tl, tm, v);
      build(tv*2 + 1, tm+1, tr, v);
      merge(tv);
    }
  }
  void update_node(int tv, ll val) {
    if(val < mx[tv]) {
      sum[tv] -= mx_c[tv] * (mx[tv] - val);
      mx[tv] = val;
    }
  }
  void push(int tv) {
    int l = tv*2, r = tv*2 + 1;
    update_node(l, mx[tv]);
    update_node(r, mx[tv]);
  }

  void update_min(int tv, int tl, int tr, int l, int r, ll val) {
    if(l > r || val >= mx[tv]) return;  // break condition: val >= mx
    if(tl == l && tr == r && smx[tv] < val) {  // tag condition: smx < val < mx
      update_node(tv, val);
      return;
    }
    else {
      push(tv);
      int tm = (tl + tr) >> 1;
      update_min(tv*2, tl, tm, l, min(tm, r), val);
      update_min(tv*2+1, tm+1, tr, max(tm+1, l), r, val);
      merge(tv);
    }
  }
  ll get_sum(int tv, int tl, int tr, int l, int r) {
    if(l > r) return 0;
    if(tl == l && tr == r) {
      return sum[tv];
    }
    else {
      push(tv);
      int tm = (tl + tr) >> 1;
      return get_sum(tv*2, tl, tm, l, min(tm, r)) + get_sum(tv*2 + 1, tm+1, tr, max(tm+1, l), r);
    }
  }
  public:
  SegtreeBeats(vector<ll>v) {
    n = v.size();
    sum = vector<ll>(4*n + 10);
    mx = vector<ll>(4*n + 10);
    smx = vector<ll>(4*n + 10);
    mx_c = vector<ll>(4*n + 10);
    build(1, 1, n, v);
  }
  void upd_min(int l, int r, ll val) {
    update_min(1, 1, n, l, r, val);
  }
  ll get(int l, int r){
    return get_sum(1, 1, n, l, r);
  }

};
