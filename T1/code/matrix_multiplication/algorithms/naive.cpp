/**
 * Referencias y Bibliografía:
 * - Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). Introduction to Algorithms (4th ed.). MIT Press.
 * - Strassen, V. (1969). Gaussian elimination is not optimal. Numerische Mathematik, 13(4), 354-356.
 */
#include <vector>

using namespace std;

vector<vector<int>> multiply_naive(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();

    vector<vector<int>> C(n, vector<int>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < p; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}