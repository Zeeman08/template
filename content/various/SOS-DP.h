/**
 * Author: Nafees
 * License: CC0
 * Source: https://codeforces.com/blog/entry/45223
 * Description: Given a fixed array A of $2^n$ integers, we need to calculate function F(x) = Sum of all A[i] such that i is a subset of x.
 * Time : O($n2^n$)
 * Status : Checked
 */

 //iterative version
for(int mask = 0; mask < (1<<N); ++mask){
	dp[mask][-1] = A[mask];	//handle base case separately (leaf states)
	for(int i = 0;i < N; ++i){
		if(mask & (1<<i))
			dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
		else
			dp[mask][i] = dp[mask][i-1];
	}
	F[mask] = dp[mask][N-1];
}
//memory optimized, super easy to code.
for(int i = 0; i<(1<<N); ++i)
	F[i] = A[i];
for(int i = 0;i < N; ++i) 
    for(int mask = 0; mask < (1<<N); ++mask){
	    if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
}