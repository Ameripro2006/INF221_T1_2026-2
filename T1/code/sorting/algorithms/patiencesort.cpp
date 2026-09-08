#include <vector>
#include <queue>
#include <algorithm>

// Estructura para almacenar elementos en la cola de prioridad (min-heap)
struct HeapNode {
    int val;        // Valor del elemento actual
    int pile_idx;   // Índice de la pila a la que pertenece

    // Operador '>' para que std::priority_queue se comporte como Min-Heap
    bool operator>(const HeapNode& other) const {
        return val > other.val;
    }
};

// ============================================================================
// FUNCIÓN PRINCIPAL: sortArray (Patience Sort)
// ============================================================================
std::vector<int> sortArray(std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    // Cada pila guarda sus elementos en orden descendente de inserción
    std::vector<std::vector<int>> piles;
    // Arreglo auxiliar con las cimas de cada pila para realizar búsqueda binaria
    std::vector<int> pile_tops;

    // FASE 1: Distribuir elementos en pilas usando búsqueda binaria
    for (int x : arr) {
        // std::lower_bound busca la primera pila cuya cima sea >= x
        auto it = std::lower_bound(pile_tops.begin(), pile_tops.end(), x);

        if (it == pile_tops.end()) {
            // No cabe en ninguna pila existente: se crea una nueva a la derecha
            piles.push_back({x});
            pile_tops.push_back(x);
        } else {
            // Se coloca en la primera pila válida y se actualiza su cima
            int idx = static_cast<int>(it - pile_tops.begin());
            piles[idx].push_back(x);
            pile_tops[idx] = x;
        }
    }

    // FASE 2: K-way merge de las pilas utilizando un Min-Heap
    std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> min_heap;

    // Insertar la cima actual (último elemento insertado) de cada pila en el heap
    for (int i = 0; i < static_cast<int>(piles.size()); ++i) {
        if (!piles[i].empty()) {
            min_heap.push({piles[i].back(), i});
            piles[i].pop_back(); // Consumir de la cima
        }
    }

    // Extraer consecutivamente el mínimo global hacia el arreglo original
    int write_idx = 0;
    while (!min_heap.empty()) {
        HeapNode top_node = min_heap.top();
        min_heap.pop();

        arr[write_idx++] = top_node.val;

        // Si la pila de donde provino el valor aún tiene cartas, metemos su nueva cima
        int p_idx = top_node.pile_idx;
        if (!piles[p_idx].empty()) {
            min_heap.push({piles[p_idx].back(), p_idx});
            piles[p_idx].pop_back();
        }
    }

    return arr;
}