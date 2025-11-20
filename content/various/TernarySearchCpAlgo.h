/**
 * Author: cp algo
 * Date: 2015-05-12
 * License: CC0
 * Source: cp algo
 * Description: f is a unimodal function in the range [l, r]. returns the max in the range.
 * Time: O(\log(b-a))
 * Status: tested
 */
double ternary_search(double l, double r) {
    double eps = 1e-9;              //set the error limit here
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);      
        double f2 = f(m2);      
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return f(l);                    
}