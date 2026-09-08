/**
 * Referencias y Bibliografía:
 * - Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). Introduction to Algorithms (4th ed.). MIT Press.
 * - Documentación estándar de C++ (std::sort y algoritmos): https://en.cppreference.com/
 */
#include <algorithm>
#include <vector>

std::vector<int> sortArray(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());  
    return arr;
}
