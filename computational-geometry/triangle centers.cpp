/*
* Description: Barycentric formulas for triangle centers
* Demo: toCartesian returns (x, y) cartesian coordinates for barycentric coordinates (a, b, c), given (A, B, C) reference points
        centroid, circumcenter, incenter, orthocenter, excenter return their namesake
* Dependencies: pt class (+, -, *, /, dot, norm2, dist2)
*/

pt toCartesian(const pt &A, const pt &B, const pt &C, double a, double b, double c)
{
    return (A * a + B * b + C * c) / (a + b + c);
}

pt centroid(const pt &A, const pt &B, const pt &C) // intersection of medians
{
    return toCartesian(A, B, C, 1, 1, 1);
}

pt circumcenter(const pt &A, const pt &B, const pt &C) // intersection of perpendicular bisectors
{
    auto a = B.dist2(C), b = C.dist2(A), c = A.dist2(B);
    return toCartesian(A, B, C, a * (b + c - a), b * (c + a - b), c * (a + b - c));
}

pt incenter(const pt &A, const pt &B, const pt &C) // intersection of internal angle bisectors
{
    auto a = sqrt(B.dist2(C)), b = sqrt(C.dist2(A)), c = sqrt(A.dist2(B));
    return toCartesian(A, B, C, a, b, c);
}

pt orthocenter(const pt &A, const pt &B, const pt &C) // intersection of altitudes
{
    auto a = B.dist2(C), b = C.dist2(A), c = A.dist2(B);
    return toCartesian(A, B, C, (a + b - c) * (c + a - b), (b + c - a) * (a + b - c), (c + a - b) * (b + c - a));
}

array <pt, 3> excenters(const pt &A, const pt &B, const pt &C) // intersection of two external angle bisectors (there's 3 pairs of sides to extend)
{
    auto a = sqrt(B.dist2(C)), b = sqrt(C.dist2(A)), c = sqrt(A.dist2(B));
    return {toCartesian(A, B, C, -a, b, c), toCartesian(A, B, C, a, -b, c), toCartesian(A, B, C, a, b, -c)};
}

int main()
{
    pt a = {1, 4}, b = {6, 1}, c = {3, 6};
    vector <pt> center(4);
    center[0] = centroid(a, b, c), center[1] = circumcenter(a, b, c), center[2] = incenter(a, b, c), center[3] = orthocenter(a, b, c);
    // Expected: (3.33, 3.66) (3.875, 3.125) (2.78078, 4.21922) (2.25 4.75)
    for (int i = 0; i < 4; i++)
        cout << "(" << center[i].x << ", " << center[i].y << ") ";
    cout << '\n';
}
