#include <vector>
#include <queue>
#include <algorithm>

struct HeapNode {
    int val;        
    int pile_idx;   

   
    bool operator>(const HeapNode& other) const {
        return val > other.val;
    }
};

std::vector<int> sortArray(std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }

    std::vector<std::vector<int>> piles;
    std::vector<int> pile_tops;

    for (int x : arr) {
        auto it = std::lower_bound(pile_tops.begin(), pile_tops.end(), x);

        if (it == pile_tops.end()) {
            piles.push_back({x});
            pile_tops.push_back(x);
        } else {
            int idx = static_cast<int>(it - pile_tops.begin());
            piles[idx].push_back(x);
            pile_tops[idx] = x;
        }
    }

    
    std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<HeapNode>> min_heap;

    for (int i = 0; i < static_cast<int>(piles.size()); ++i) {
        if (!piles[i].empty()) {
            min_heap.push({piles[i].back(), i});
            piles[i].pop_back(); 
        }
    }

    int write_idx = 0;
    while (!min_heap.empty()) {
        HeapNode top_node = min_heap.top();
        min_heap.pop();

        arr[write_idx++] = top_node.val;

        int p_idx = top_node.pile_idx;
        if (!piles[p_idx].empty()) {
            min_heap.push({piles[p_idx].back(), p_idx});
            piles[p_idx].pop_back();
        }
    }

    return arr;
}