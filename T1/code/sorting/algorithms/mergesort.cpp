#include <vector>

/*
FUNCION: merge
Combina dos mitades ya ordenadas
Se apoya en el buffer temporal temp para no sobreescribir en arr
*/
void merge(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right){
    int i= left; //Puntero de lectura para la mitad izquierda
    int j=mid+1; //Puntero de lectura para la mitad derecha
    int k= left; //Puntero de escritura en el vector auxiliar temp

    //Mientras ambos subarreglos tengan elementos por comparar
    while (i<=mid && j <=right){
        if(arr[i]<=arr[j]){
            temp[k]=arr[i];
            i++;
        }else{
            temp[k]=arr[j];
            j++;
        }
        k++;
    }
    //Si quedaron elementos sobreantes en la mitad izquierda, se vacian directo
    while (i<=mid){
        temp[k]=arr[i];
        i++;
        k++;
    }
    //Si quedaron elementos en la derecha
    while (j<=right){
        temp[k]=arr[j];
        j++;
        k++;
    }

    //Copiar el bloque combinado y ordenado desde temp de vuelta a arr
    for(int idx= left; idx<=right;++idx){
        arr[idx]=temp[idx];
    }
}
/*
FUNCION: mergesortrecursive
Divide el problema en las mitades recursivamente hasta llegar al caso base de arreglos 1
*/
void mergeSortRecursive(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
    // Caso base: subarreglo de 1 elemento (left == right) o inválido (left > right)
    if (left >= right) {
        return;
    }

    // Cálculo del punto medio evitando desbordamiento de enteros (overflow)
    int mid = left + (right - left) / 2;

    // 1. DIVIDIR & VENCER: Ordenar mitad izquierda [left ... mid]
    mergeSortRecursive(arr, temp, left, mid);

    // 2. DIVIDIR & VENCER: Ordenar mitad derecha [mid + 1 ... right]
    mergeSortRecursive(arr, temp, mid + 1, right);

    // 3. COMBINAR: Mezclar ambas mitades ordenadas en tiempo lineal O(n)
    merge(arr, temp, left, mid, right);
}
/*
FUNCION PRINCIPAL: mergesort
Punto de entrada que inicializa el buffer auxiliar una sola vez
*/
void mergeSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    std::vector<int> temp(arr.size());
    mergeSortRecursive(arr, temp, 0, static_cast<int>(arr.size()) - 1);
}

// Interfaz obligatoria que espera el programa principal sorting.cpp
std::vector<int> sortArray(std::vector<int>& arr) {
    mergeSort(arr);
    return arr;
}