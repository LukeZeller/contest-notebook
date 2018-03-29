/*
* Description: vertex shifting
* Demo: shift = 0 -> moves vertices s.t. poly[0] is the lowest point
*       otherwise rotates indices of vertex by shift places
* Dependency: polygon prerequisites
*/

polygon rotateVertices(polygon &poly, int shift = 0)
{
    if (shift == 0) shift = min_element(poly.begin(), poly.end()) - poly.begin();
    polygon res(poly.size());
    for (int i = 0; i < poly.size(); i++)
    {
        res[i] = poly[(i + shift) % poly.size()];
    }
    return res;
}

int main()
{
    polygon poly = {{0, 0}, {0, 10}, {10, 20}, {20, 10}, {10, 0}};
    polygon rotated = rotateVertices(poly, 3);
    //Expected: (20, 10) (10, 0) (0, 0) (0, 10) (10, 20)
    for (pt p: rotated) cout<<"("<<p.x<<", "<<p.y<<") "; cout<<'\n';
    polygon original = rotateVertices(rotated);
    //Expected: (0, 0) (0, 10) (10, 20) (20, 10) (10, 0)
    for (pt p: original) cout<<"("<<p.x<<", "<<p.y<<") "; cout<<'\n';
}
