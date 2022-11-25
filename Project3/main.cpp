#include <bits/stdc++.h>
#include "kdtree.hpp"

int read() {
    int x=0, f=1; int ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

int main() {
    std::vector<std::pair<std::tuple<int, int>, int>> v;
    v.emplace_back(std::make_tuple(1, 2), 1);
    v.emplace_back(std::make_tuple(2, 3), 2);
    v.emplace_back(std::make_tuple(3, 4), 3);
    v.emplace_back(std::make_tuple(4, 5), 4);
    v.emplace_back(std::make_tuple(5, 1), 5);
    KDTree<std::tuple<int, int>, int> t(v);
    printf("%d\n", t.find({1,2})->second);
    printf("%d\n", t.findMin<0>()->second);
    printf("%d\n", t.findMax<0>()->second);
    printf("%d\n", t.findMin<1>()->second);
    printf("%d\n", t.findMax<1>()->second);

    for (auto it = t.begin(); it != t.end(); ++it) {
        printf("%d ", it->second);
    }
    puts("");
    t.erase({4,5});
    for (auto it = t.begin(); it != t.end(); ++it) {
        printf("%d ", it->second);
    }
    puts("");
    return 0;
}