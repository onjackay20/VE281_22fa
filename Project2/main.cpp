#include <vector>
#include <iostream>
#include <time.h>
#include <unordered_map>
#include <list>
#include <chrono>
#include "copy.hpp"
#include "hashtable.hpp"
#define ll long long
#define N 1000010

int read() {
    int x = 0, f = 1, ch = getchar();
    for (; ch < '0' || ch>'9'; ch = getchar()) if (ch == '-') f = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * f;
}

class Value {
public:
    int val;
    Value(): val(-1) {}
    Value(int val): val(val) {}
};

int x[N], y[N];

int main() {
    int n = 100000, m = 10000;
    srand(static_cast<unsigned int>(time(NULL)));
    HashTable<size_t, Value> ht;
    std::unordered_map<size_t, Value> um;
    std::list<std::pair<size_t, Value>> lst;

    for (int i = 0; i < n; i++) {
        x[i] = rand()%3, y[i] = rand()%m;
    }

    auto start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        if (x[i] == 0) {
            ht.insert(y[i], Value(i));
        }
        if (x[i] == 1) {
            ht.erase(y[i]);
        }
        if (x[i] == 2) {
            ht[y[i]].val;
        }
    }
    auto end1 = std::chrono::steady_clock::now();
    auto start2 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        if (x[i] == 0) {
            um[y[i]] = Value(i);
        }
        if (x[i] == 1) {
            um.erase(y[i]);
        }
        if (x[i] == 2) {
            um[y[i]].val;
        }
    }
    auto end2 = std::chrono::steady_clock::now();

    auto start3 = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        auto find_y = [i](std::pair<size_t, Value> a) {
            return static_cast<int>(a.first) == y[i];
        };
        auto it = std::find_if(lst.begin(), lst.end(), find_y);
        if (x[i] == 0) {
            if (it != lst.end()) 
                it->second.val = i;
            else lst.emplace_front(y[i], Value(i));
            // printf("insert %d %d\n", y, i);
        }
        if (x[i] == 1) {
            if (it != lst.end()) lst.erase(it);
            // printf("erase %d\n", y);
        }
        if (x[i] == 2) {
            if (it == lst.end()) {
                lst.emplace_front(y[i], Value());
                it = lst.begin();
            }
            it->second.val;
            // printf("%d %d %d\n", ht[y].val, um[y].val, it->second.val);
        }
    }
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
    std::cout << "elapsed time of HashTable:        " << elapsed_seconds1.count() << "s\n";
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    std::cout << "elapsed time of unordered_map:    " << elapsed_seconds2.count() << "s\n";
    std::chrono::duration<double> elapsed_seconds3 = end3 - start3;
    std::cout << "elapsed time of list:             " << elapsed_seconds3.count() << "s\n";
    return 0;
}