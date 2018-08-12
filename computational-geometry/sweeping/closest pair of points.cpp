/*
* Description: closest pair of points (via line sweep)
* Demo: given vector of points returns pair of closest points
* Dependencies: pt class
*/

inline ptT square(ptT i) {return i * i;}

pair <pt, pt> closestPairPoints(vector <pt> &points)
{
    sort(points.begin(), points.end(), [](pt a, pt b){return make_pair(a.x, a.y) < make_pair(b.x, b.y);});
    set <pt> window = {points[0]};

    ptlT closest = INF;
    pair <pt, pt> res;
    for (int i = 1, left = 0; i < points.size(); i++)
    {
        while(i > left and square(points[i].x - points[left].x) > closest) window.erase(points[left++]);

        pt lb = {points[i].x, (ptsT) ceil(points[i].y - sqrt(closest))}; //PS: remove ceil if using doubles
        pt ub = {points[i].x, (ptsT) floor(points[i].y + sqrt(closest))}; //PS: remove floor if using doubles
        for (auto it = window.lower_bound(lb); it != window.upper_bound(ub); it++)
        {
            auto dist = it -> dist2(points[i]);
            if (dist < closest) closest = dist, res = {*it, points[i]};
        }
        window.insert(points[i]);
    }
    return res;
}
