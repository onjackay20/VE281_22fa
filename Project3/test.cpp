#include <bits/stdc++.h>
#define ll long long
// #define N 100010

int read() {
    int x=0, f=1; char ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

template<size_t N>
void f() {
    if (N == 0) return;
    printf("N = %d\n", N);
    f<(N+1)%5>();
}

class test
{
private:
    /* data */
    int a, b;
public:
    test(int a, int b) : a(a), b(b) {};
};

typedef std::vector<int> Vector;
void g(Vector::iterator start, Vector::iterator end) {
    for (auto i = start; i != end; i++) {
        printf("%d\n", *i);
    }
}

int main() {
    // f<2>();
    // test s(2,3),t(1, 2);
    // t = test(1, 2);
    // std::less<test>{}(s, t);

    Vector v{1, 2, 3, 4};
    auto it = v.begin();
    it = it + 1;
    std::sort(it, it + 2, [](int a, int b) {
        return a<b;
    });
    return 0;
}