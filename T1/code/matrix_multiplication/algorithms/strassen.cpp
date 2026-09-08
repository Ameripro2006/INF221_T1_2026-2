#include <vector>

using namespace std;

// Suma de matrices termino a termino
vector<vector<int>> add_matrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Resta de matrices termino a termino
vector<vector<int>> sub_matrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Implementacion recursiva principal de Strassen
vector<vector<int>> multiply_strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Caso base: matriz de 1x1
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int k = n / 2;

    // Inicializacion de submatrices de k x k
    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)),
                        A21(k, vector<int>(k)), A22(k, vector<int>(k));
    vector<vector<int>> B11(k, vector<int>(k)), B12(k, vector<int>(k)),
                        B21(k, vector<int>(k)), B22(k, vector<int>(k));

    // Descomposicion en cuadrantes
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Calculo de las 7 multiplicaciones recursivas de Strassen
    vector<vector<int>> M1 = multiply_strassen(add_matrices(A11, A22), add_matrices(B11, B22));
    vector<vector<int>> M2 = multiply_strassen(add_matrices(A21, A22), B11);
    vector<vector<int>> M3 = multiply_strassen(A11, sub_matrices(B12, B22));
    vector<vector<int>> M4 = multiply_strassen(A22, sub_matrices(B21, B11));
    vector<vector<int>> M5 = multiply_strassen(add_matrices(A11, A12), B22);
    vector<vector<int>> M6 = multiply_strassen(sub_matrices(A21, A11), add_matrices(B11, B12));
    vector<vector<int>> M7 = multiply_strassen(sub_matrices(A12, A22), add_matrices(B21, B22));

    // Combinacion de submatrices resultantes
    vector<vector<int>> C11 = add_matrices(sub_matrices(add_matrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = add_matrices(M3, M5);
    vector<vector<int>> C21 = add_matrices(M2, M4);
    vector<vector<int>> C22 = add_matrices(sub_matrices(add_matrices(M1, M3), M2), M6);

    // Reconstruccion de la matriz final C de n x n
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            C[i][j]         = C11[i][j];
            C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}