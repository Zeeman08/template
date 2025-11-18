/**
 * Author: Nafees
 * Description: Solution to CF813-F 
 * Source: (jiangly)
 * Status: (cf-checked)
 */

struct DSU {
    std::vector<std::pair<int &, int>> his;
    
    int n;
    std::vector<int> f, g, bip;
    
    DSU(int n_) : n(n_), f(n, -1), g(n), bip(n, 1) {}
    
    std::pair<int, int> find(int x) {
        if (f[x] < 0) {
            return {x, 0};
        }
        auto [u, v] = find(f[x]);
        return {u, v ^ g[x]};
    }
    
    void set(int &a, int b) {
        his.emplace_back(a, a);
        a = b;
    }
    
    void merge(int a, int b, int &ans, int &comp) {
        auto [u, xa] = find(a);
        auto [v, xb] = find(b);
        int w = xa ^ xb ^ 1;
        if (u == v) {
            if (bip[u] && w) {
                set(bip[u], 0);
                ans--;
            }
            return;
        }
        if (f[u] > f[v]) {
            std::swap(u, v);
        }
        comp--;
        ans -= bip[u];
        ans -= bip[v];
        set(bip[u], bip[u] && bip[v]);
        set(f[u], f[u] + f[v]);
        set(f[v], u);
        set(g[v], w);
        ans += bip[u];
    }
    
    int timeStamp() {
        return his.size();
    }
    
    void rollback(int t) {
        while (his.size() > t) {
            auto [x, y] = his.back();
            x = y;
            his.pop_back();
        }
    }
};
int main() 
{	
    int n, m; cin >> n >> m;
    map<array<int, 2>, int> mp;
    const int N = (1<<(__lg(m)+2));
    vector<vector<array<int, 2>>> ed(N);
    auto add = [&] (auto add, int p, int l, int r, int x, int y, array<int, 2>e) -> void {
        if(l >= y || r <= x) return;
        if(l >= x && r <= y) {
            ed[p].emplace_back(e);
            return;
        }
        int m = (l+r)>>1;
        add(add, (p<<1), l, m, x, y, e);
        add(add, (p<<1)^1, m, r, x, y, e);
    };
    F0R(i, m) {
        int u, v; cin >> u >> v;
        u--; v--;
        if(mp.find({u, v})==mp.end()) {
            mp[{u, v}] = i;
        }
        else {
            add(add, 1, 0, m, mp[{u, v}], i, {u, v});
            mp.erase({u, v});
        }
    }
    trav(u, mp) {
        add(add, 1, 0, m, u.s, m, u.f);
    }

    DSU d(n);
    vector<int> ans(m);
    auto dfs = [&] (auto dfs, int p, int l, int r, int bip, int comp) -> void {
        int t = d.timeStamp();
        trav(u, ed[p]) {
            d.merge(u[0], u[1], bip, comp);
        }
        if(r-l==1) {
            ans[l] = (bip==comp);
        }
        else {
            int m = (l+r)>>1;
            dfs(dfs, (p<<1), l, m, bip, comp);
            dfs(dfs, (p<<1)^1, m, r, bip, comp);
        }
        d.rollback(t);
    };
    dfs(dfs, 1, 0, m, n, n);
    trav(u, ans) {
        cout << (u ? "YES" : "NO") << "\n";
    }
    return 0;
}   