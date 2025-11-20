/**
 * Author: Nafees
 * License: CC0
 * Source: snuke-san
 * Description: Given n integers, find l-th to r-th integers that can be formed by xor-ing any subset of the integers.
 */

int n; ll l, r; cin >> n >> l >> r;
vector<ll> basis(60);
F0R(i, n) {
    ll u; cin >> u;
    F0R(j, 60) {
        u = min(u, u^basis[j]);
    }
    if(u==0) continue;
    ROF(j, 59, 0) {
        if(u>>j&1) {
            F0R(k, 60) {
                if(basis[k]>>j&1) {
                    basis[k] ^= u;
                }
            }
            basis[j] = u;
            break;
        }
    }
}

l--;
vector<ll> need;
F0R(i, 60) if(basis[i]) need.push_back(basis[i]);
for(ll k = l; k < r; ++k) {
    ll ans = 0;
    F0R(i, need.size()) {
        if(k>>i&1) ans ^= need[i]; 
    }
    cout << ans << " ";
}
