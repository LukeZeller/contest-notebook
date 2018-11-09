/*
* Description: convert points in manhattan metric: |x2 - x1| + |y2 - y1| to chebyshev metric: max(|x2 - x1|, |y2 - y1|)
* Application: To find longest path if a point can go to all points within lines w/ slope 1/r and -1/r
*              scale all points with r (so 90 degrees between lines)
*              then convert to chebyshev, sort lexicographically by (x, y) [ie. first by x, tie-break w/ y]
*              then find longest non-decreasing subsequence wrt y
*/

pt toChebyshev(pt p)
{
    return {p.x + p.y, p.x - p.y};
}
