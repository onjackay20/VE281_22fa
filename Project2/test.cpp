#include <bits/stdc++.h>
#define ll long long
#define N 100010

int read() {
    int x = 0, f = 1; char ch = getchar();
    for (; ch < '0' || ch>'9'; ch = getchar()) if (ch == '-') f = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * f;
}

class C {
public:
    int x;
    C(): x(114514) {}
    C(int _x) : x(_x) {}
};

void f(C c) {
    printf("%d\n", c.x);
}

int main() {
    f(C());
    return 0;
}