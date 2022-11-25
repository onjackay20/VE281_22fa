#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <vector>
#include <stdlib.h>
#include <functional>

template<typename T, typename Compare>
void bubble_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    for (size_t i = 0; i < vector.size(); i++) {
        int flag = 0;
        for (size_t j = 1; j < vector.size() - i; j++) {
            if (comp(vector[j], vector[j - 1])) {
                std::swap(vector[j - 1], vector[j]);
                flag = 1;
            }
        }
        if (!flag) 
            return;
    }
}

template<typename T, typename Compare>
void insertion_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    for (size_t i = 1; i < vector.size(); i++) {
        size_t k = std::upper_bound(vector.begin(), vector.begin() + i, vector[i], comp) - vector.begin();
        if (k == i) continue;
        T temp = vector[i];
        for (size_t j = i - 1; j >= k; j--) {
            vector[j + 1] = vector[j];
            if (j == k) break;
        }
        vector[k] = temp;
    }
}

template<typename T, typename Compare>
void selection_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    for (size_t i = 0; i < vector.size(); i++) {
        size_t k = i;
        for (size_t j = i + 1; j < vector.size(); j++) {
            if (comp(vector[j], vector[k]))
                k = j;
        }
        std::swap(vector[i], vector[k]);
    }
}

template<typename T, typename Compare>
void merge_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    if (vector.size() <= 1)
        return;
    size_t mid = vector.size() / 2;
    std::vector<T> l(vector.begin(), vector.begin() + mid);
    std::vector<T> r(vector.begin() + mid, vector.end());
    merge_sort(l, comp);
    merge_sort(r, comp);
    size_t i = 0, j = 0, k = 0;
    while (i < l.size() && j < r.size()) {
        if (!comp(r[j], l[i]))
            vector[k++] = l[i++];
        else 
            vector[k++] = r[j++];
    }
    while (i < l.size())
        vector[k++] = l[i++];
    while (j < r.size())
        vector[k++] = r[j++];
}

template<typename T, typename Compare>
void quick_sort_extra(std::vector<T> &vector, Compare comp = std::less<T>()) {
    if (vector.size() <= 1)
        return;
    srand(static_cast<unsigned int> (time(NULL)));
    size_t t = rand() % vector.size();
    std::vector <T> l, r;
    for (size_t i = 0; i < vector.size(); i++) {
        if (i == t) continue;
        if (comp(vector[i], vector[t])) 
            l.push_back(vector[i]);
        else
            r.push_back(vector[i]);
    }
    quick_sort_extra(l, comp);
    quick_sort_extra(r, comp);
    size_t k = 0;
    T temp = vector[t];
    for (T x: l) vector[k++] = x;
    vector[k++] = temp;
    for (T x: r) vector[k++] = x;
}

template<typename T, typename Compare>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = std::less<T>()) {
    srand(static_cast<unsigned int> (time(NULL)));
    if (vector.size() <= 1)
        return;
    std::vector<std::pair<int, int> > q;
    q.emplace_back(0, vector.size() - 1);
    while (!q.empty()) {
        int l = q.back().first, r = q.back().second;
        q.pop_back();
        T t = vector[rand() % (r - l + 1) + l];
        int i = l, j = r;
        while (i <= j) {
            while (comp(vector[i], t) && i <= j) i++;
            while (comp(t, vector[j]) && i <= j) j--;
            if (i <= j) {
                T temp = vector[i];
                vector[i] = vector[j];
                vector[j] = temp;
                i++, j--;
            }
        }
        if (l < j)
            q.emplace_back(l, j);
        if (i < r) 
            q.emplace_back(i, r);
    }
    q.clear();
}

#endif //VE281P1_SORT_HPP