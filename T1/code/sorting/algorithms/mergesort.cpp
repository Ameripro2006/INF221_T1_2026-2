#include <vector>


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


void mergeSortRecursive(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
    // Caso base: subarreglo de 1 elemento (left == right) o invalido (left > right)
    if (left >= right) {
        return;
    }

    // Calculo del punto medio evitando desbordamiento de enteros (overflow)
    int mid = left + (right - left) / 2;

    // Ordenar mitad izquierda 
    mergeSortRecursive(arr, temp, left, mid);

    // Ordenar mitad derecha 
    mergeSortRecursive(arr, temp, mid + 1, right);

    // 3.Mezclar ambas mitades ordenadas en tiempo lineal O(n)
    merge(arr, temp, left, mid, right);
}

void mergeSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    std::vector<int> temp(arr.size());
    mergeSortRecursive(arr, temp, 0, static_cast<int>(arr.size()) - 1);
}


std::vector<int> sortArray(std::vector<int>& arr) {
    mergeSort(arr);
    return arr;
}