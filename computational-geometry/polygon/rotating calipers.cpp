/*
* Description: Rotating calipers for finding antipodal point pairs or point-edge pairs
* Demo: Rotating calipers technique for finding diameter of convex polygon
*/

const pt origin = {0, 0};
ptT rotatingCalipers(const polygon &poly) // Assumes that poly is given in clockwise orientation and that no three vertices are collinear
{
    int n = poly.size();
    if (n < 2)
      return 0; // PS: Return value if poly is a degenerate polygon
    long double res = -INF; /*PS*/
    for (int i = 0, j = 1; i < n; ++i)
    {
        for(; ; j = next(j, n))
        {
            res = max(res, sqrt(poly[i].dist2(poly[j]))); // PS: Place calculation after inner for loop if looking for point parallel to poly[i] - poly[i + 1] line
            if (orientation(origin, poly[i + 1] - poly[i], poly[next(j, n)] - poly[j]) != 1)
                break;
        }
    }
    return res;
}
