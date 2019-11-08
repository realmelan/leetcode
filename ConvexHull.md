# Convex Hull
Given a set of n points, find all points which when connected constituent the outer bound of a polygon which covers all points.

A simple algorithm is Gift wrapping alogrithm, a.k.a. Jarvis march. From the leftmost point, p0, sequentially find the next point, p1,
such that all other points are on the left of the edge p0->p1, etc.
```
let pl = left most point

let endpoint = pl
while true:
  start = endpoint
  for i in 1 to n:
      if pi is on the left of start->endpoint:
          endpoint = pi
  if endpoint = pl:
      break
  add endpoint to convex hull
```

Here given p0->p1, p0->p2, how to test whether p2 is on the right of p0->p1?
cross product of p0->p1, p0->p2, would help. 

let crossProduct(p0, p1, p2) = (p1x-p0x)*(p2y-p0y) - (p2x-p0x)*(p1y-p0y).
* crossProduct(p0,p1,p2) = 0  => p0, p1,p2 are colinear
* crossProduct(p0,p1,p2) > 0  => p2 is on the left of p0->p1
* crossProduct(p0,p1,p2) < 0  => p2 is on the right of p0->p1

# Problems:
* https://leetcode.com/problems/convex-polygon
* https://leetcode.com/problems/erect-the-fence/

# Ref
* https://en.wikipedia.org/wiki/Convex_hull_algorithms
* https://en.wikipedia.org/wiki/Gift_wrapping_algorithm
* https://en.wikipedia.org/wiki/Cross_product#Computational_geometry
