/**
 * Author: Me
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Same convention as above, just a bit better constant factor. 
    Suitable for dense Grid. For the sparse one, n is around 1e9
 * Status: stress-tested
 */
#pragma once
struct FT2D {
  vector<vector<ll>> s;
  int n, m;
  FT2D(int r, int c) : n(r), m(c), s(r, vector<ll>(c, 0)) {}
  void update(int r, int c, ll dif) { 
      for (int i = r; i < n; i |= i + 1) {
          for (int j = c; j < m; j |= j + 1) {
              s[i][j] += dif;
          }
      }
  }
  ll query(int r, int c) { 
      ll res = 0;
      for (int i = r; i > 0; i &= i - 1) {
          for (int j = c; j > 0; j &= j - 1) {
              res += s[i-1][j-1];
          }
      }
      return res;
  }
};