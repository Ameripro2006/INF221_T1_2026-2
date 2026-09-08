# Documentación

## Entrega

La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

## Multiplicación de matrices

Algoritmos evaluados: **Naive clasico** ($\mathcal{O}(N^3)$) y **Strassen** ($\mathcal{O}(N^{\log_2 7}) \approx \mathcal{O}(N^{2.81})$).

### Programa principal

* **Compilación:**

    cd matrix_multiplication
    make

  Genera el ejecutable `matrix_multiplication` en el directorio actual.

* **Ejecución:**

    ./matrix_multiplication

  No recibe argumentos por linea de comandos, al ejecutarse:
  1. Recorre `data/matrix_input/` en busca de todos los casos de prueba, identificando cada caso por sus archivos `<caso>_1.txt` y `<caso>_2.txt`.
  2. Para cada caso encontrado, calcula el producto con **ambos** algoritmos (`naive` y `strassen`) en la misma ejecucion.

* **Salida:**
  * Imprime por consola el progreso, el tiempo (ms) y el consumo de memoria máxima (Peak RSS en KB) medido con `getrusage` para cada caso y algoritmo.
  * Escribe los resultados en `data/measurements/results.csv` (columnas: `algoritmo,archivo,tamano,tiempo_ms,memoria_kb`) — el archivo se sobreescribe al inicio de cada ejecución del programa
  * Guarda la matriz resultante de cada caso en `data/matrix_output/<caso>_out.txt`.

### Scripts

* `scripts/matrix_generator.py`: Genera las matrices sinteticas segun dimension, estructura y dominio numerico, guardandolas en `data/matrix_input/`
* `scripts/run_benchmarks.py`: Compila y ejecuta `matrix_multiplication`.
* `scripts/plot_generator.py`: Lee `data/measurements/results.csv` y genera los graficos comparativos de tiempo y memoria en `data/plots/`

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, PatienceSort, std::sort

### Programa principal

* **Compilación:**

    cd sorting
    make

  Genera **cuatro binarios independientes** en `bin/`: `mergesort`, `quicksort`, `sort` y `patiencesort`. Cada uno vincula el mismo `sorting.cpp` (lectura, medicion y registro) con la implementacion especicfica del algoritmo en `algorithms/<algoritmo>.cpp`

* **Ejecución:**

    ./bin/<algoritmo> <archivo_entrada.txt> [archivo_salida.txt]

  * `<algoritmo>`: no es un argumento, sino el nombre del binario a ejecutar (`mergesort`, `quicksort`, `sort` o `patiencesort`).
  * `<archivo_entrada.txt>`: ruta al archivo con los enteros del arreglo a ordenar (ubicados en `data/array_input/`).
  * `[archivo_salida.txt]` (opcional): ruta donde guardar el arreglo ya ordenado.

* **Salida:**
  * Imprime por consola: `<algoritmo> | n=<tamaño> | Tiempo: <ms> ms | Memoria: <kb> KB`.
  * Verifica la correctitud con `std::is_sorted` (si falla, imprime una alerta por `stderr`, pero no detiene la ejecución). en casos extremos en arreglos grandes ordenados pueden provocar Stack Overflow en QuickSort.
  * Agrega (append) una fila a `data/measurements/results.csv` (columnas: `algoritmo,archivo,tamano,tiempo_ms,memoria_kb,ordenado`) por cada ejecucion — a diferencia del CSV de matrices, este se va acumulando.

### Scripts

* `scripts/array_generator.py`: Construye los archivos con los arreglos de prueba para los distintos $N$ y patrones en `data/array_input/`
* `scripts/run_benchmarks.py`: Ejecuta cada uno de los cuatro binarios (`bin/mergesort`, `bin/quicksort`, `bin/sort`, `bin/patiencesort`) sobre cada archivo de `data/array_input/`
* `scripts/plot_generator.py`: Procesa `data/measurements/results.csv` y exporta las curvas log-log y graficos de barras de rendimiento y consumo de memoria a `data/plots/`