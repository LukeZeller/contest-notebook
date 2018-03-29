/*
* Description: shoelace theorem for finding simple polygon area
* Demo: shoelaces are doubled oriented area (negative for cw)
* Dependency: convex polygon base
*/

vector <ptT> getShoelaces(polygon &poly)
{
    int sz = poly.size();
    vector <ptT> shoelace(sz + 1);
    for (int i = 0; i < sz; i++)
    {
        shoelace[i + 1] = shoelace[i] + (poly[i] ^ poly[next(i, sz)]); //Caution !! returns doubled/oriented area -> cw: negative
    }
    return shoelace;
}

ptT polygonArea(polygon &poly){return getShoelaces(poly)[poly.size()];}

int main()
{
    polygon poly = {{6, -1}, {0, 0}, {0, 5}, {3, 8}, {5, 5}};
    auto shoelace = getShoelaces(poly);

    //Expected: 0 0 0 -15 -40 -75
    for (ptT i: shoelace) cout<<i<<" ";
    cout<<'\n';
    //Expected: -75
    cout<<polygonArea(poly)<<'\n';
}
