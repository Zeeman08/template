/**
 * Author: Nafees
 * License: CC0
 * Source: AlphaQ
 * Description: Sort a set of point in counterclockwise order
 */

inline bool up (point p) {
  return p.y > 0 or (p.y == 0 and p.x >= 0);
}

sort(v.begin(), v.end(), [] (point a, point b) {
  return up(a) == up(b) ? a.x * b.y > a.y * b.x : up(a) < up(b);
});