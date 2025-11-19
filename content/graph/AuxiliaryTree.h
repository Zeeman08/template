/**
 * Author: Nafees
 * Description: Get the virtual tree for each color id
 * Source: (snuke-san)
 * Status: (ABC-340G)
 */

vector<vector<int>> to2(n);
rep(ci,n) { // ci = color id
    vector<int>& vs = cvs[ci];
    // cvs = nodes of that col
    if (vs.size() == 0) continue;
    sort(vs.begin(), vs.end(), [&](int a, int b) {
        return in[a] < in[b];});
    int m = vs.size();
    rep(i,m-1) {
        vs.push_back(lca(vs[i],vs[i+1]));
    }
    sort(vs.begin(), vs.end(),[&](int a, int b) { 
        return in[a] < in[b];});
    vs.erase(unique(vs.begin(), vs.end()),vs.end());
    {
        vector<int> st;
        for (int v : vs) {
            while (st.size()) {
                int p = st.back();
                if (in[p] < in[v] && in[v] < out[p]) break;
                st.pop_back();
            }
            if (st.size()) to2[st.back()].push_back(v);
            st.push_back(v);
        }
    }
    // process aux tree
    for (int v : vs) to2[v] = vector<int>();
}