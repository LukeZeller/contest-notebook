/**
 * Description: RREF and related derived operations on matrices.
 *      - RREF (updates matrix, returns elementary operations)
 *      - Matrix determinant
 *      - Matrix inversion
 * Dependency: Matrix struct, type, and operations (matrix.cpp)
 */

long double EPS = 0.00000001;

/* For debugging */
void print(const matrix &M) {
    for (auto& row : M) {
        for (auto elem: row)
            cout << (abs(elem) < EPS ? 0 : elem) << " ";
        cout << endl;
    }
}

enum elem_op_t {
    r_swap, r_scale, r_add
};

/* Interpretation: 
   if op == swap:
       M[r0], M[r1] <- M[r1], M[r0]
   if op == scale:
       M[r0] <- mult * M[r0]
   if op == add:
        M[r1] <- M[r1] + mult * M[r0]
*/
struct elem_op {
    elem_op_t op;
    int r0, r1;
    matT mult;

    void execute(matrix& M) const {
        if (op == r_swap) {swap(M[r0], M[r1]); return;}
        if (op == r_scale) for (int i = 0; i < M[0].size(); ++i) M[r0][i] *= mult;
        else for (int i = 0; i < M[0].size(); ++i) M[r1][i] += mult * M[r0][i];
    }
};

vector<elem_op> rref(matrix& M) {
    vector<elem_op> ops;
    int r = 0, c = 0, n_r = M.size(), n_c = M[0].size();
    while (c < n_c) {
        int r2 = r;
        while (r2 < n_r && M[r2][c] == 0) ++r2;
        if (r2 == n_r) {++c; continue;}
        if (r2 > r) {
            ops.push_back({r_swap, r, r2, 0});
            ops.back().execute(M);
        }
        if (abs(M[r][c] - 1) > EPS) {  /* Remove EPS comparison for integer / finite field */
            ops.push_back({r_scale, r, 0, 1 / M[r][c]});
            ops.back().execute(M);
        }
        for (int r_itr = 0; r_itr < n_r; ++r_itr) {
            if (r_itr == r) continue;
            if (abs(M[r_itr][c]) > EPS) { /* Remove EPS comparison for integer / finite field */
                ops.push_back({r_add, r, r_itr, -M[r_itr][c]});
                ops.back().execute(M);
            }
        }
        ++r, ++c;
    }
    return ops;
}

matT det(matrix M) {
    auto ops = rref(M);
    matT d = 1;
    for (const auto& op : ops) {
        if (op.op == r_swap) d = -d;
        if (op.op == r_scale) d /= op.mult;
    }
    return d;
}

matrix inverse(matrix M) {
    auto ops = rref(M);
    matrix res(M.size(), M.size());
    for (int i = 0; i < M.size(); ++i) res[i][i] = 1;
    for (const auto& op : ops) op.execute(res);
    return res;
}

int main() {
    cout << setprecision(10);
    int n = 4;
    /* Test with Vandermonde matrix */
    vector<matT> seq = {1, 3.14159, -2.223456, 18.5};
    matT expected_d = 1;
    matrix m(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            m[i][j] = pow(seq[i], j);
            if (j > i) expected_d *= (seq[j] - seq[i]);
        }

    auto m_inv = inverse(m);
    auto d = det(m);

    cout << "Actual Determinant: " << setprecision(10) << d << endl;
    cout << "Expected Determinant: " << expected_d << endl;
    // Should be identity (but actually off by a bunch of numbers of about 10^-20)
    print(m * m_inv);

    for (int i = 0; i < n; i++)
        m[i][3] = m[i][2] + 3 * m[i][1] - .5 * m[i][0];
    // Expect 0
    cout << det(m) << endl;

    // Expect -4
    matrix m2(2, 2);
    m2[0][1] = m2[1][0] = 2;
    cout << det(m2) << endl;

    print(inverse(m2));
}
