/**
 * Author: Anachor
 * Date: 2016
 * Description: there will be exactly 2 polygons both of them are convex, given 
 * in the counterclockwise order and have non-zero areas. Furthermore, 
 * in one polygon a vertex won't be on the sides of the other one. print 
 * on a single line, a single number representing the area of intersection, 
 * rounded to four decimal places.
 * Time: O((N+M)log(N+M))
 * Status: stress-tested
 */

#include <bits/stdc++.h>
using namespace std;

typedef double Tf;
typedef double Ti;            
const Tf PI = acos(-1), EPS = 1e-9;

// --- Basic Geometry Structs and Functions ---
int dcmp(Tf x) { return abs(x) < EPS ? 0 : (x<0 ? -1 : 1);}

struct Point {
    Ti x, y;
    Point(Ti x = 0, Ti y = 0) : x(x), y(y) {}

    Point operator + (const Point& u) const { return Point(x + u.x, y + u.y); }
    Point operator - (const Point& u) const { return Point(x - u.x, y - u.y); }
    Point operator * (const Tf u) const { return Point(x * u, y * u); }
    Point operator / (const Tf u) const { return Point(x / u, y / u); }

    bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
    friend istream &operator >> (istream &is, Point &p) { return is >> p.x >> p.y; }
};

Ti cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

// --- Linear Namespace (Only essential intersection logic) ---
namespace Linear {
    // lines are represented as a ray from a point: (point, vector)
    // returns false if two lines (p, v) && (q, w) are parallel or collinear
    // true otherwise, intersection point is stored at o via reference
    bool lineLineIntersection(Point p, Point v, Point q, Point w, Point& o) {
        if(dcmp(cross(v, w)) == 0) return false;
        Point u = p - q;
        o = p + v * (cross(w,u)/cross(v,w));
        return true;
    }
} 

// --- Polygonal Namespace (Only Area) ---
typedef vector<Point> Polygon;
namespace Polygonal {
    Tf signedPolygonArea(const Polygon &p) {
        Tf ret = 0;
        for(int i = 0; i < (int) p.size() - 1; i++)
            ret += cross(p[i]-p[0],  p[i+1]-p[0]);
        return ret / 2;
    }
}

// --- HalfPlanar Namespace (The Core Solution) ---
namespace HalfPlanar {
    using Linear::lineLineIntersection;
    
    struct DirLine {
        Point p, v;
        Tf ang;
        DirLine() {}
        /// Directed line containing point P in the direction v
        DirLine(Point p, Point v) : p(p), v(v) { ang = atan2(v.y, v.x); }
        
        bool operator<(const DirLine& u) const { return ang < u.ang; }
        bool onLeft(Point x) const { return dcmp(cross(v, x-p)) >= 0; }
    };

    // Returns the region bounded by the left side of some directed lines
    // Complexity: O(n log n) for sorting, O(n) afterwards
    Polygon halfPlaneIntersection(vector<DirLine> li) {
        int n = li.size(), first = 0, last = 0;
        sort(li.begin(), li.end());
        vector<Point> p(n);
        vector<DirLine> q(n);
        q[0] = li[0];

        for(int i = 1; i < n; i++) {
            while(first < last && !li[i].onLeft(p[last - 1])) last--;
            while(first < last && !li[i].onLeft(p[first])) first++;
            q[++last] = li[i];
            if(dcmp(cross(q[last].v, q[last-1].v)) == 0) {
                last--;
                if(q[last].onLeft(li[i].p)) q[last] = li[i];
            }
            if(first < last)
                lineLineIntersection(q[last - 1].p, q[last - 1].v, q[last].p, q[last].v, p[last - 1]);
        }

        while(first < last && !q[first].onLeft(p[last - 1])) last--;
        if(last - first <= 1) return {};
        lineLineIntersection(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);
        return Polygon(p.begin()+first, p.begin()+last+1);
    }
}

// --- Main Driver ---
void solve() {
    int N, M;
    if (!(cin >> N >> M)) return; // Check for read failure

    using namespace HalfPlanar;
    vector<DirLine> lines;

    // Read Polygon A
    vector<Point> polyA(N);
    for(int i = 0; i < N; i++) cin >> polyA[i];
    for(int i = 0; i < N; i++) {
        Point u = polyA[i];
        Point v = polyA[(i + 1) % N];
        // Add directed line u -> v
        lines.emplace_back(u, v - u);
    }

    // Read Polygon B
    vector<Point> polyB(M);
    for(int i = 0; i < M; i++) cin >> polyB[i];
    for(int i = 0; i < M; i++) {
        Point u = polyB[i];
        Point v = polyB[(i + 1) % M];
        // Add directed line u -> v
        lines.emplace_back(u, v - u);
    }

    // Calculate intersection polygon
    Polygon intersectionPoly = halfPlaneIntersection(lines);

    // Calculate area
    double ans = Polygonal::signedPolygonArea(intersectionPoly);
    cout << setprecision(4) << fixed << fabs(ans) << endl;
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}