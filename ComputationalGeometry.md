
# Cross Product of points p0, p1, p2
Given p0->p1, p0->p2, how to test whether p2 is on the right of p0->p1? cross product of p0->p1, p0->p2, would help.

let crossProduct(p0, p1, p2) = (p1x-p0x)(p2y-p0y) - (p2x-p0x)(p1y-p0y).

crossProduct(p0,p1,p2) = 0 => p0, p1,p2 are colinear
crossProduct(p0,p1,p2) > 0 => p2 is on the left of p0->p1
crossProduct(p0,p1,p2) < 0 => p2 is on the right of p0->p1

# Distance of point p0 to a line by p1, p2

distance(p0, p1p2) = ((p2x-p1x)*p0y - (p2y-p1y)*p0x + p1x*p2y - p2x*p1y) / sqrt((p2y-p1y)^2 + (p2x-p1x)^2)

Note, the sign of the result tells whther p1->p0 is on upper side of p1->p2 or not.

# Reference
* https://en.wikipedia.org/wiki/Cross_product#Computational_geometry
* https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
