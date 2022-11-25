#include "sort.hpp"
#include <bits/stdc++.h>

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    std::vector<int> a;
    int N = 5000;
    for (int i = 0; i < N; i++) a.push_back(rand() % (int) 1e9);
    // bubble_sort(a, std::less<int>());
    // selection_sort(a, std::less<int>());
    // insertion_sort(a, std::less<int>());
    merge_sort(a, std::less<int>());
    // quick_sort_extra(a, std::less<int>());
    // quick_sort_inplace(a, std::less<int>());
    for (int i = 1; i < N; i++) 
        if (std::less<int>()(a[i], a[i-1]))
            puts("Error");
    return 0;
}