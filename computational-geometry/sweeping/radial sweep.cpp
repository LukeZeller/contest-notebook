/*
* Description: radial sweep
* Demo: sortByAngleRay sorts points in order that ray extended from origin hits them (starts horizontal left, goes cw)
        sortByAngleLine sorts points in order than line from origin hits them (starts horizontal, goes cw)
* Dependencies: pt class
*/

struct polarCmp //Caution !! need to make sure origin is not in list being sorted
{
    const pt o;

    polarCmp(const pt &origin) : o(origin) {}
    bool operator () (const pt &a, const pt &b) const
    {
        int orient = orientation(o, a, b);
        return orient == 1 or (orient == 0 and a < b);
    }
};

vector <pt> sortByAngleRay(vector <pt> points, const pt &origin)
{
    polarCmp cmp(origin);
    auto first = partition(points.begin(), points.end(), [&origin](const pt &p){return p == origin;});
    auto pivot = partition(first, points.end(), [&origin](const pt &p){return origin < p;});
    sort(points.begin(), pivot, cmp);
    sort(pivot, points.end(), cmp);
    return points;
}

vector <pt> sortByAngleLine(vector <pt> points, const pt &origin) // Caution!! Requires that a bool rf parameter is in the pt class
{
    polarCmp cmp(origin);
    auto first = partition(points.begin(), points.end(), [&origin](const pt &p){return p == origin;});
    auto pivot = partition(first, points.end(), [&origin](const pt &p){return p.y == origin.y;});
    for (pt &p: points)
    {
        if (p.y >= origin.y) p.rf = false;
        else p = p.reflect(origin), p.rf = true;
    }
    sort(pivot, points.end(), cmp);
    for (pt &p: points) if (p.rf)
        p = p.reflect(origin);
    return points;
}

int main()
{
    vector <pt> points = {{30, 30}, {60, 30}, {100, 20}, {70, 40}, {110, 40}, {40, 50}, {80, 70}};
    auto res1 = sortByAngleRay(points, {70, 40});

    //Expected: (70, 40), (40, 50), (80, 70), (110, 40), (100, 20), (60, 30), (30, 30)
    for (pt p: res1) cout<<"("<<p.x<<", "<<p.y<<") ";
    cout<<'\n';

    auto res2 = sortByAngleLine(points, {70, 40});
    //Expected: (70, 40), (110, 40), (40, 50), (100, 20), (80, 70), (60, 30), (30, 30)
    for (pt p: res2) cout<<"("<<p.x<<", "<<p.y<<") ";
    cout<<'\n';
}
