/**
 * Author: Me
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: as it says.
 * Status: tested
 */
typedef Point<ll> P;
P dir;
bool half(P p){
    return dir.cross(p) < 0 || (dir.cross(p) == 0 && dir.dot(p) > 0);
}

bool polarComp(P p, P q) {
    return make_tuple(half(p), 0) < make_tuple(half(q), p.cross(q));
}
void process(vector<P> &P) {
    int mnid = 0;
    for (int i=0; i<P.size(); i++)
        if (P[i] < P[mnid])
            mnid = i;
    rotate(P.begin(), P.begin()+mnid, P.end());
}
vector<P> MinkowskiSum(vector<P> A, vector<P> B){
    process(A);
    process(B);

    int n = A.size(), m = B.size();
    vector<P> PP(n), QQ(m);
    for(int i = 0; i < n; i++) PP[i] = A[(i+1)%n] - A[i];
    for(int i = 0; i < m; i++) QQ[i] = B[(i+1)%m] - B[i];

    dir = P(0, -1);
    vector<P> C(n+m+1);
    merge(PP.begin(), PP.end(), QQ.begin(), QQ.end(), C.begin()+1, polarComp);
    C[0] = A[0] + B[0];

    for(int i = 1; i < C.size(); i++) C[i] = C[i] + C[i-1];
    C.pop_back();
    return C;
}
