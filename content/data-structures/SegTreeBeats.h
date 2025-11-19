/**
 * Author: Me
 * Date: 2014-11-28
 * License: CC0
 * Source: Folklore
 * Description: range chmin and range add operations and range sum queries.
 * Status: Tested on CF
 */
#pragma once

struct SegtreeBeats {
  vector<long long> sum, mx, smx, mx_c, lz_add;
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
  void build(int tv, int tl, int tr, vector<long long> &v) {
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
  void add_to_node(int tv, int tl, int tr, long long val) {
    mx[tv] += val;
    smx[tv] += val;
    sum[tv] += val * (tr-tl+1);
    lz_add[tv] += val;
  }
  void update_node(int tv, long long val) {
    if(val < mx[tv]) {
      sum[tv] -= mx_c[tv] * (mx[tv] - val);
      mx[tv] = val;
    }
  }
  void push(int tv, int tl, int tr) {
    int tm = (tl + tr) / 2;
    int l = tv*2, r = tv*2 + 1;
    add_to_node(l, tl, tm, lz_add[tv]);
    add_to_node(r, tm+1, tr, lz_add[tv]);
    lz_add[tv] = 0;
    update_node(l, mx[tv]);
    update_node(r, mx[tv]);
  }

  void update_min(int tv, int tl, int tr, int l, int r, long long val) {
    if(l > r || val >= mx[tv]) return;  // break condition: val >= mx
    if(tl == l && tr == r && smx[tv] < val) {  // tag condition: smx < val < mx
      update_node(tv, val);
      return;
    }
    else {
      push(tv, tl, tr);
      int tm = (tl + tr) >> 1;
      update_min(tv*2, tl, tm, l, min(tm, r), val);
      update_min(tv*2+1, tm+1, tr, max(tm+1, l), r, val);
      merge(tv);
    }
  }
  void update_add(int tv, int tl, int tr, int l, int r, long long val) {
    if(l > r) return;
    if(tl == l && tr == r) {
      add_to_node(tv, tl, tr, val);
    } 
    else {
      push(tv, tl, tr);
      int tm = (tl + tr) >> 1;
      update_add(tv*2, tl, tm, l, min(tm, r), val);
      update_add(tv*2+1, tm+1, tr, max(tm+1, l), r, val);
      merge(tv);
    }
  }
  long long get_sum(int tv, int tl, int tr, int l, int r) {
    if(l > r) return 0;
    if(tl == l && tr == r) {
      return sum[tv];
    }
    else {
      push(tv, tl, tr);
      int tm = (tl + tr) >> 1;
      return get_sum(tv*2, tl, tm, l, min(tm, r)) + get_sum(tv*2 + 1, tm+1, tr, max(tm+1, l), r);
    }
  }
  
  SegtreeBeats(vector<long long>v) {
    n = v.size();
    sum = vector<long long>(4*n + 10);
    mx = vector<long long>(4*n + 10);
    smx = vector<long long>(4*n + 10);
    mx_c = vector<long long>(4*n + 10);
    lz_add = vector<long long>(4*n + 10);
    build(1, 1, n, v);
  }
  void upd_min(int l, int r, long long val) {
    update_min(1, 1, n, l, r, val);
  }
  long long get(int l, int r){
    return get_sum(1, 1, n, l, r);
  }
  void upd_add(int l, int r, long long val) {
    update_add(1, 1, n, l, r, val);
  }
};
