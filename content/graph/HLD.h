/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/LazySegmentTree.h"

template<bool VALS_IN_EDGES> struct HLD { 
	int N; vector<vi> adj;  
	vi par, root, depth, sz, pos;
	int ti; vi rpos;
    lazy_segtree<S, op, e, F, 
    mapping, composition, id> tree;
    HLD(int N) : N(N), adj(N), par(N), root(N),
     depth(N), sz(N), pos(N), tree(N) {}
	void ae(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfsSz(int x) { 
		sz[x] = 1; 
		trav(y,adj[x]) {
			par[y] = x; depth[y] = depth[x]+1;
			adj[y].erase(find(all(adj[y]),x));
			dfsSz(y); sz[x] += sz[y];
			if (sz[y] > sz[adj[x][0]]) swap(y,adj[x][0]);
		}
	}
	void dfsHld(int x) {
		pos[x] = ti++; rpos.pb(x);
		trav(y,adj[x]) {
			root[y] = (y == adj[x][0] ? root[x] : y);
			dfsHld(y); }
	}
	void init(vector<tuple<int, int, int>> ed, int R = 0) {
        // ed is empty if the edge has
        // no initial weight
        // for node: tree.set(pos[node],val)
        par[R] = depth[R] = ti = 0; dfsSz(R); 
		root[R] = R; dfsHld(R); 
        for(auto [u, v, c] : ed) {
            int idx=-1;
            if(u==par[v]) idx=pos[v];
            else idx=pos[u];
            tree.set(idx, {c, 1});
        }
	}
	int lca(int x, int y) {
		for (; root[x] != root[y]; y = par[root[y]])
			if (depth[root[x]] > depth[root[y]]) swap(x,y);
		return depth[x] < depth[y] ? x : y;
	}
	template <class BinaryOp>
	void processPath(int x, int y, BinaryOp op) {
		for (; root[x] != root[y]; y = par[root[y]]) {
			if (depth[root[x]] > depth[root[y]]) swap(x,y);
			op(pos[root[y]],pos[y]); }
		if (depth[x] > depth[y]) swap(x,y);
		op(pos[x]+VALS_IN_EDGES,pos[y]); 
	}
	void modifyPath(int x, int y, int v) { 
		processPath(x,y,[this,&v](int l, int r) { 
			tree.apply(l,r+1,F(v)); }); }
	mint queryPath(int x, int y) { 
		mint res = e().x; 
		processPath(x,y,[this,&res](int l, int r) { 
			res += tree.prod(l,r+1).x; });
		return res; }
	void modifySubtree(int x, int v) { 
		tree.apply(pos[x]+VALS_IN_EDGES,pos[x]+sz[x]-1,F(v)); }
};
