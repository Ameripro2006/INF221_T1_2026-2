#include <vector>
#include <utility> // Para std::swap

// ============================================================================
// FUNCIÓN: partition (Esquema de Lomuto)
// Selecciona arr[right] como pivote. Reorganiza el subarreglo de modo que
// los elementos <= pivote queden a la izquierda y los mayores a la derecha.
// Retorna el índice definitivo donde queda posicionado el pivote.
// ============================================================================
int partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[right]; // Pivote: último elemento del rango
    int i = left - 1;       // Frontera de los elementos menores o iguales al pivote

    // Puntero explorador 'j' recorre desde left hasta right - 1
    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    // Colocar el pivote en su posición final definitiva (justo después de los menores)
    std::swap(arr[i + 1], arr[right]);
    
    return i + 1; // Retorna el índice de la posición final del pivote
}

// ============================================================================
// FUNCIÓN: quickSortRecursive
// Divide el problema alrededor del pivote y se llama recursivamente.
// ============================================================================
void quickSortRecursive(std::vector<int>& arr, int left, int right) {
    // Caso base: subarreglo de 0 o 1 elemento (left >= right)
    if (left >= right) {
        return;
    }

    // 1. PARTICIÓN: Coloca el pivote en su posición correcta pIndex
    int pIndex = partition(arr, left, right);

    // 2. VENCER: Ordenar recursivamente los elementos a la izquierda del pivote
    quickSortRecursive(arr, left, pIndex - 1);

    // 3. VENCER: Ordenar recursivamente los elementos a la derecha del pivote
    quickSortRecursive(arr, pIndex + 1, right);
}

// ============================================================================
// FUNCIÓN PRINCIPAL: sortArray
// Punto de entrada compatible con el marco de pruebas (sorting.cpp).
// ============================================================================
std::vector<int> sortArray(std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    quickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1);

    return arr;
}