#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

// Declaración externa de la función que implementa cada algoritmo
std::vector<int> sortArray(std::vector<int>& arr);

int main(int argc, char* argv[]) {
    // Uso esperado: ./bin/<algoritmo> <ruta_archivo_entrada> [ruta_archivo_salida]
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_entrada.txt> [archivo_salida.txt]" << std::endl;
        return 1;
    }

    std::string input_path = argv[1];
    std::string output_path = (argc >= 3) ? argv[2] : "";

    // 1. Lectura rápida del archivo de entrada
    std::ifstream in_file(input_path);
    if (!in_file.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada: " << input_path << std::endl;
        return 1;
    }

    std::vector<int> data;
    data.reserve(1000000); // Reserva inicial para optimizar memoria
    int val;
    while (in_file >> val) {
        data.push_back(val);
    }
    in_file.close();

    size_t n = data.size();

    // 2. Medición estricta del algoritmo (sin contar lectura/escritura de disco)
    auto start = std::chrono::high_resolution_clock::now();
    data = sortArray(data);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    double elapsed_ms = duration_ms.count();

    // 3. Verificación de corrección
    bool is_sorted = std::is_sorted(data.begin(), data.end());
    if (!is_sorted) {
        std::cerr << "ALERTA: El arreglo NO quedo ordenado correctamente." << std::endl;
    }

    // 4. Extraer metadatos a partir del nombre del archivo y del ejecutable
    fs::path p(input_path);
    std::string filename = p.stem().string(); // Ej: 1000_aleatorio_D1_a
    fs::path bin_path(argv[0]);
    std::string algo_name = bin_path.filename().string(); // Ej: mergesort, quicksort

    // 5. Registrar medición en formato CSV dentro de data/measurements/
    fs::create_directories("data/measurements");
    std::string csv_file = "data/measurements/results.csv";

    // Si el CSV no existe, escribimos la cabecera
    bool write_header = !fs::exists(csv_file);
    std::ofstream out_csv(csv_file, std::ios::app);
    if (out_csv.is_open()) {
        if (write_header) {
            out_csv << "algoritmo,archivo,tamano,tiempo_ms,ordenado\n";
        }
        out_csv << algo_name << ","
                << filename << ","
                << n << ","
                << elapsed_ms << ","
                << (is_sorted ? "si" : "no") << "\n";
        out_csv.close();
    }

    // 6. Opcional: escribir el arreglo ordenado si se solicitó ruta de salida
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

    std::cout << algo_name << " | n=" << n << " | Tiempo: " << elapsed_ms << " ms" << std::endl;

    return 0;
}