
/**
 * Author: Nafees
 * Description: As name suggests
 * Source: (Nafees)
 * Status: (OCPC2025S-D2I)
 */

vector<set<int>> ap;
// (id, l, r)
auto dnc = [&] (auto dnc, int x, int l, int r) -> void {
    if(r-l<1) return;
    ap.push_back({});        
    auto [val, m] = ST.prod(l, r); 
    // m is the partition point 
    int c1 = ap.size();
    dnc(dnc, ap.size(), l, m);
    int c2 = ap.size();
    dnc(dnc, ap.size(), m+1, r);  
    int c3 = ap.size();
    if(c1==c2 && c2==c3) {
        ap[x].insert(p[l]);
    }
    else if(c1==c2) {
        swap(ap[x], ap[c2]);
        ap[x].insert(p[m]);
    }
    else if(c2==c3) {
        swap(ap[x], ap[c1]);
        ap[x].insert(p[m]);
    }
    else {
        swap(ap[x], ap[c2]);
        pair<int, int> to_src = {l, m};
        if(m-l > r-(m+1)) {
            swap(ap[x], ap[c1]);
            to_src = {m+1, r};
        }
        FOR(i, to_src.f, to_src.s-1) {
            // do processing first
            ans += ap[x].count(p[m]-p[i]);
        }
        FOR(i, to_src.f, to_src.s-1) {
            // merging of two segments
            ap[x].insert(p[i]);
        }
        // merging of two segments and midpoint
        ap[x].insert(p[m]);
    }
};
dnc(dnc, 0, 0, n); 