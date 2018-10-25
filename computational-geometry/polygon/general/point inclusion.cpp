/*
* Description: winding number test for whether point in inside polygon - polygon can have self intersections and/or holes
* Demo: returns -1/0/1 depending on whether point is inside, on, or outside polygon
* Dependency: pt class (==, -, ^, orientation, polygon next)
*/

// Assumes points are given in clockwise order
int pointInPolygon(const polygon &poly, const pt &p)
{
    int winding = 0, n = poly.size();
    for (int i = 0; i < n; i++)
    {
        int j = next(i, n);
        if (p == poly[i])
            return 0;
        if (abs(poly[i].y - poly[j].y) < EPS and abs(poly[i].y - p.y) < EPS) // PS: replace EPS checks if integer type
        {
            auto mn = min(poly[i].x, poly[j].x), mx = max(poly[i].x, poly[j].x);
            if (mn <= p.x and p.x <= mx)
                return 0;
        }
        else
        {
            bool above = p.y > poly[i].y;
            if (above != (p.y > poly[j].y))
            {
                auto orient = orientation(p, poly[j], poly[i]);
                if (orient == 0)
                    return 0;
                else if(above == (orient == 1))
                    winding += above ? 1 : -1;
            }
        }
    }
    return winding == 0 ? 1 : -1;
} // inside: -1, outside: 1, on: 0

int main()
{
    pt a = {0, 0}, b = {0, 5}, c = {5, 5}, d = {5, 0};
    polygon poly = {a, b, c, d};
    // Expected: 0 0 -1
    cout << pointInPolygon(poly, {5, 3}) << " " << pointInPolygon(poly, {0, 5}) << " " << pointInPolygon(poly, {3, 3}) << '\n';
    // Expected: 1 1
    cout << pointInPolygon(poly, {6, 0}) << " " << pointInPolygon(poly, {-1, -1}) << '\n';
}
