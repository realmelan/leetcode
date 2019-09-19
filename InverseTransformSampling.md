Inverse transform sampling provides a way to generate a desired random distribution, using a uniform random distribution.

Here are the steps:
1. find Probability density function on x, PDF(X)
1. compute cumulative density function on x, CDF(X)
1. reverse y and x to CDF(X) to get CDF_r(X).

This CDF_r(X) is the new random distribution function.

Suppose we want to generate a uniform distribution in a circle of R. A point can be determined by how far it is from center,
and the angle it is from the 0 angle line:
* angle = 360 * unif()
* distance = F(unif())

How do we get F(x)?

we know at 2*x distance, there are 2 times # of points than at x distance, it means PDF(x) = 2x;
then CDF(x) = x^2, which means y = x^2. Now reverse x and y, x = y^2, then y = sqrt(x).
so, distance = sqrt(unif()).

# Problems
* https://leetcode.com/problems/generate-random-point-in-a-circle/

# Ref
* https://en.wikipedia.org/wiki/Inverse_transform_sampling
* https://programming.guide/generate-random-value-with-distribution.html (More intuitive)
