/*
* Description: andrew monotone chain algorithm for finding convex hull
* Demo: returns points in clockwise order, can be adjusted to also return boundary points
*/

polygon andrewMonotoneChain(polygon &points)
{
    sort(points.begin(), points.end());
    polygon hull;
    for (int i = 0; i < 2; i++)
    {
        int s = hull.size();
        for (pt &p: points)
        {
            while(hull.size() >= s + 2 and orientation(hull.rbegin()[1], hull.rbegin()[0], p) != 1) //PS: change to == -1 to get boundary points
                hull.pop_back();
            hull.push_back(p);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
    if (hull.size() == 2 and hull[0] == hull[1]) hull.pop_back();
    return hull;
}
