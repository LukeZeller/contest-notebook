/*
* Description: shoelace theorem for finding simple polygon area
* Demo: shoelaces are doubled oriented area (negative for cw)
* Dependency: pt class
*/

vector <ptT> getShoelaces(polygon &poly) //Caution !! returns doubled/oriented area -> cw: negative, ccw: positive
{
    int sz = poly.size();
    vector <ptT> shoelace(sz + 1);
    for (int i = 0; i < sz; i++)
        shoelace[i + 1] = shoelace[i] + (poly[i] ^ poly[next(i, sz)]); 
    return shoelace;
}

ptT polygonArea(polygon &poly) //Caution !! returns doubled/oriented area -> cw: negative, ccw: positive
{
    int sz = poly.size();
    ptT sol = 0;
    for (int i = 0; i < sz; i++)
        sol += poly[i] ^ poly[next(i, sz)]; 
    return sol;
}

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
