/*
* Description: andrew monotone chain algorithm for finding convex hull
* Demo: returns points in clockwise order, can be adjusted to also return boundary points
* Dependency: convex polygon base
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

int main()
{
    polygon poly = {{10, 20}, {0, 0}, {10, 0}, {20, 10}, {0, 10}, {5, 5}};
    auto hull = andrewMonotoneChain(poly);

    //Expected: (0, 0) (0, 10) (10, 20) (20, 10) (10, 0)
    for (pt p: hull) cout<<"("<<p.x<<", "<<p.y<<") "; cout<<'\n';

    return 0;
}
