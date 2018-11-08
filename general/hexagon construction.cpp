/*
* Description: Hexagon Graph Construction
* Demo: dy/dx vectors for hexagon traversal and constructHexagon(r) builds hexgonal graph w/ side length r (vertex for exterior face is g.size() - 1)
*/

vector <int> dx = {0, -1, -1, 0, 1, 1};
vector <int> dy_top = {-1, -1, 0, 1, 1, 0};
vector <int> dy_mid = {-1, -1, 0, 1, 0, -1};
vector <int> dy_bottom = {-1, 0, 1, 1, 0, -1};

graph constructHexagon(int r)
{
    int sz = r * r * r - (r - 1) * (r - 1) * (r - 1);
    int exterior = sz;

    graph g(sz + 1);
    vector <vector<int>> grid(2 * r - 1);
    for (int i = 0, it = 0, len = r; i < 2 * r - 1; i++)
    {
        for (int j = 0; j < len; j++)
            grid[i].push_back(it++);
        len += (i + 1 < r) ? 1 : -1;
    }
    for (int i = 0; i < 2 * r - 1; i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            int curr = grid[i][j];
            for (int k = 0; k < 6; k++)
            {
                int nx = i + dx[k], ny;
                if (i + 1 == r)
                    ny = j + dy_mid[k];
                else if(i + 1 < r)
                    ny = j + dy_top[k];
                else
                    ny = j + dy_bottom[k];

                if (nx < 0 or nx >= 2 * r - 1 or ny < 0 or ny >= grid[nx].size())
                {
                    g[curr].push_back({exterior});
                    g[exterior].push_back({curr});
                }
                else
                {
                    int neighbor = grid[nx][ny];
                    g[curr].push_back({neighbor});
                }
            }
        }
    }
    return g;
}
