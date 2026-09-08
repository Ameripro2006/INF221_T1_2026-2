/**
 * Programa principal para medicion de tiempos de multiplicacion de matrices
 * INF-221 Algoritmos y Complejidad
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <algorithm>

#include "algorithms/naive.cpp"
#include "algorithms/strassen.cpp"

namespace fs = std::filesystem;
using namespace std;
using namespace std::chrono;

// Lee una matriz desde un archivo de texto
vector<vector<int>> read_matrix(const string& filepath) {
    ifstream infile(filepath);
    vector<vector<int>> matrix;
    string line;

    while (getline(infile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> row;
        int val;
        while (ss >> val) {
            row.push_back(val);
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }
    return matrix;
}

// Guarda la matriz calculada en el archivo _out.txt
void write_matrix(const string& filepath, const vector<vector<int>>& matrix) {
    ofstream outfile(filepath);
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            outfile << matrix[i][j] << (j + 1 == matrix[i].size() ? "" : " ");
        }
        outfile << "\n";
    }
}

int main() {
    string input_dir = "data/matrix_input/";
    string output_dir = "data/matrix_output/";
    string measurements_dir = "data/measurements/";

    fs::create_directories(output_dir);
    fs::create_directories(measurements_dir);

    ofstream csv_out(measurements_dir + "results.csv");
    csv_out << "algoritmo,archivo,tamano,tiempo_ms\n";

    // Recolectar prefijos de casos base a partir de archivos terminados en _1.txt
    vector<string> cases;
    for (const auto& entry : fs::directory_iterator(input_dir)) {
        string filename = entry.path().filename().string();
        if (filename.find("_1.txt") != string::npos) {
            string base_name = filename.substr(0, filename.length() - 6); // Quita '_1.txt'
            cases.push_back(base_name);
        }
    }

    sort(cases.begin(), cases.end());

    cout << "Casos encontrados para evaluar: " << cases.size() << endl;

    for (const auto& base_case : cases) {
        string file_a = input_dir + base_case + "_1.txt";
        string file_b = input_dir + base_case + "_2.txt";

        if (!fs::exists(file_b)) {
            continue;
        }

        // Obtener dimension n desde el nombre del archivo ({n}_{t}_{d}_{m})
        stringstream ss(base_case);
        string n_str;
        getline(ss, n_str, '_');
        int n = stoi(n_str);

        cout << "Procesando: " << base_case << " (n=" << n << ")..." << flush;

        vector<vector<int>> A = read_matrix(file_a);
        vector<vector<int>> B = read_matrix(file_b);

        // 1. Evaluacion Naive
        auto start = high_resolution_clock::now();
        vector<vector<int>> C_naive = multiply_naive(A, B);
        auto stop = high_resolution_clock::now();
        double duration_naive = duration<double, milli>(stop - start).count();

        csv_out << "naive," << base_case << "," << n << "," << duration_naive << "\n";
        write_matrix(output_dir + base_case + "_out.txt", C_naive);

        // 2. Evaluacion Strassen
        start = high_resolution_clock::now();
        vector<vector<int>> C_strassen = multiply_strassen(A, B);
        stop = high_resolution_clock::now();
        double duration_strassen = duration<double, milli>(stop - start).count();

        csv_out << "strassen," << base_case << "," << n << "," << duration_strassen << "\n";

        cout << " [Naive: " << duration_naive << " ms | Strassen: " << duration_strassen << " ms]" << endl;
        csv_out.flush();
    }

    csv_out.close();
    cout << "\nExperimentos completados con exito. Archivo guardado en " << measurements_dir << "results.csv\n";
    return 0;
}