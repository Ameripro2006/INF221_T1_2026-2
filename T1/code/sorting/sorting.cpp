#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <algorithm>
#include <sys/resource.h>

namespace fs = std::filesystem;

std::vector<int> sortArray(std::vector<int>& arr);

int main(int argc, char* argv[]) {
    // Uso esperado: ./bin/<algoritmo> <ruta_archivo_entrada> [ruta_archivo_salida]
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_entrada.txt> [archivo_salida.txt]" << std::endl;
        return 1;
    }

    std::string input_path = argv[1];
    std::string output_path = (argc >= 3) ? argv[2] : "";

    std::ifstream in_file(input_path);
    if (!in_file.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada: " << input_path << std::endl;
        return 1;
    }

    std::vector<int> data;
    data.reserve(1000000); 
    int val;
    while (in_file >> val) {
        data.push_back(val);
    }
    in_file.close();

    size_t n = data.size();

    auto start = std::chrono::high_resolution_clock::now();
    data = sortArray(data);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    double elapsed_ms = duration_ms.count();

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    long memoria_kb = usage.ru_maxrss;

    bool is_sorted = std::is_sorted(data.begin(), data.end());
    if (!is_sorted) {
        std::cerr << "ALERTA: El arreglo NO quedo ordenado correctamente." << std::endl;
    }

    fs::path p(input_path);
    std::string filename = p.stem().string(); // Ej: 1000_aleatorio_D1_a
    fs::path bin_path(argv[0]);
    std::string algo_name = bin_path.filename().string(); // Ej: mergesort, quicksort

    fs::create_directories("data/measurements");
    std::string csv_file = "data/measurements/results.csv";

    bool write_header = !fs::exists(csv_file);
    std::ofstream out_csv(csv_file, std::ios::app);
    if (out_csv.is_open()) {
        if (write_header) {
            out_csv << "algoritmo,archivo,tamano,tiempo_ms,memoria_kb,ordenado\n";
        }
        out_csv << algo_name << ","
                << filename << ","
                << n << ","
                << elapsed_ms << ","
                << memoria_kb << ","
                << (is_sorted ? "si" : "no") << "\n";
        out_csv.close();
    }

    if (!output_path.empty()) {
        fs::create_directories(fs::path(output_path).parent_path());
        std::ofstream out_arr(output_path);
        if (out_arr.is_open()) {
            for (size_t i = 0; i < data.size(); ++i) {
                out_arr << data[i] << (i + 1 == data.size() ? "" : " ");
            }
            out_arr.close();
        }
    }

    std::cout << algo_name << " | n=" << n << " | Tiempo: " << elapsed_ms << " ms | Mem: " << memoria_kb << " KB" << std::endl;

    return 0;
}