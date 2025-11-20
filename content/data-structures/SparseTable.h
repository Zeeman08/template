/**
 * Author: Me
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Gives range minimum in constant time
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
struct SparseTable {
    vector<vector<int>> st;
    int n, K;
    SparseTable() {}
    SparseTable(vector<int>a) {
        n = a.size(); K = __lg(n) + 1;
        st = vector<vector<int>>(K, vector<int>(n));
        for(int i = 0; i < n; i++) st[0][i] = a[i];
        for (int i = 1; i < K; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    int get(int L, int R) {
        int i = __lg(R - L + 1);
        return min(st[i][L], st[i][R - (1 << i) + 1]);
    }
};