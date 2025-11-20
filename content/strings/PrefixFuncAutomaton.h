/**
 * Author: Me
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: If the current prefix function value is i 
 * (i.e., you've matched the first i characters of string s), and you now append the character 'a' + c, 
 * then: aut[i][c] gives the new value of the prefix function for the updated string.
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
void compute_automaton(string s, vector<vector<int>>& aut) {
    s += '#';
    int n = s.size();
    vector<int> pi = prefix_function(s);
    aut.assign(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}
