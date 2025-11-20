/**
 * Author: cp algo
 * Date: 2019-12-28
 * License: CC0
 * Description: Just Mo's Algo. The current template considers 0-based indexing.
 * Time: O(N \sqrt Q)
 * Status: copied from cp algo
 */
#pragma once
void remove(idx); void add(idx); int get_answer();  
int block_size;
struct Query {
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};
vector<int> mo_s_algorithm(vector<Query> queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());
    int cur_l = 0, cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries) {
        while (cur_l > q.l) {cur_l--;add(cur_l);}
        while (cur_r < q.r) {cur_r++;add(cur_r);}
        while (cur_l < q.l) {remove(cur_l);cur_l++;}
        while (cur_r > q.r) {remove(cur_r);cur_r--;}
        answers[q.idx] = get_answer();
    }
    return answers;
}