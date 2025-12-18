/**
 * Author: Rubaiyat
 * License: CC0
 * Source: Rubaiyat
 * Description: use dbg(v) where v is any container, or primitive, or pairs etc.
 */
template<typename T>
void _print(const T &x) { cerr << x; }
template<typename A, typename B>
void _print(const pair<A, B> &p) {
    cerr << "("; _print(p.first); cerr << ", "; _print(p.second); cerr << ")";
}
template<typename T>
void _print(const vector<T> &v) {
    cerr << "[ ";
    for (auto &x : v) { _print(x); cerr << " "; }
    cerr << "]";
}
template<typename T>
void _print(const set<T> &s) {
    cerr << "{ ";
    for (auto &x : s) { _print(x); cerr << " ";}
    cerr << "}";
}
template<typename K, typename V>
void _print(const map<K, V> &m) {
    cerr << "{ ";
    for (auto &x : m) { _print(x); cerr << " "; }
    cerr << "}";
}
#define dbg(x) cerr << #x << ": ", _print(x), cerr << "\n"
