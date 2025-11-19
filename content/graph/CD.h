/**
 * Author: Nafees
 * Description: O(NlogN) decomposition of a tree
 * Source: (snuke-san)
 * Status: (ABC-359G)
 */

vector<bool> used(n);
vector<int> sz(n);
auto cd = [&] (auto cd, int v) -> void {
    auto getCentroid = [&] () {
        auto dfs = [&](auto f, int v, int p=-1) -> int {
            sz[v] = 1;
            for (int u : adj[v]) {
            if (u == p || used[u]) continue;
                sz[v] += f(f,u,v);
            }
            return sz[v];
        };
        int tot = dfs(dfs,v), c = -1;
        auto dfs2 = [&](auto f, int v, int p=-1) -> void {
            bool ok = (tot-sz[v])*2 <= tot;
            for (int u : adj[v]) {
                if (u == p || used[u]) continue;
                f(f,u,v);
                if (sz[u]*2 > tot) ok = false;
            }
            if (ok) c = v;
        };
        dfs2(dfs2,v);
        return c;
    };
    int c = getCentroid();

    // take care of centroid here
    for (int u : adj[c]) {
        if (used[u]) continue;

        auto dfs = [&](auto f, int v, int p=-1, int dep=1) -> void {
            
            for (int u : adj[v]) {
                if (u == p || used[u]) continue;
                f(f,u,v,dep+1);
            }
        };
        dfs(dfs,u);
        
    }
    for (int u : adj[c]) {
        if (used[u]) continue;
        cd(cd,u);
    }
};
