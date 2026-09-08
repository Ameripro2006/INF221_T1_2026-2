#include <vector>
#include <utility> 


int partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[right]; // Pivote: último elemento del rango
    int i = left - 1;       // Frontera de los elementos menores o iguales al pivote

    // Puntero explorador j recorre desde left hasta right - 1
    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    // Colocar el pivote en su posicion final definitiva (justo despues de los menores)
    std::swap(arr[i + 1], arr[right]);
    
    return i + 1; // Retorna el indice de la posicion final del pivote
}


void quickSortRecursive(std::vector<int>& arr, int left, int right) {
    // Caso base: subarreglo de 0 o 1 elemento (left >= right)
    if (left >= right) {
        return;
    }

    //Coloca el pivote en su posición correcta pIndex
    int pIndex = partition(arr, left, right);

    //Ordenar recursivamente los elementos a la izquierda del pivote
    quickSortRecursive(arr, left, pIndex - 1);

    //Ordenar recursivamente los elementos a la derecha del pivote
    quickSortRecursive(arr, pIndex + 1, right);
}

std::vector<int> sortArray(std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    quickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1);

    return arr;
}