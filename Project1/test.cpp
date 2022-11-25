#include <bits/stdc++.h>
#define ll long long
#define N 100010

int read() {
    int x=0, f=1; char ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

void f(std::vector <int> &&u) {
    for (auto x: u) x++;
}

void qs(int *a, int l, int r) {
    if (l>=r) return;
    int t = rand() % (r-l+1) + l;
    int i=l, j=r;
    printf("%d %d\n", l, r);
    while (i <= j) {
        while (a[i] < a[t]) i++;
        while (a[j] > a[t]) j--;
        if (i<=j) {
            std::swap(a[i], a[j]);
            puts("?");
            i++, j--;
        }
    }
    printf("%d %d %d\n", t, i, j);
    for (int i=0; i<6; i++) printf("%d ", a[i]);
    puts("");
    qs(a, l, j);
    qs(a, i, r);
    return;
}

int main() {
    srand(time(NULL));
    int a[10]={1,4,6,2,4,7};
    qs(a, 0, 5);
    for (int i=0; i<6; i++) printf("%d ", a[i]);
    puts("");
    return 0;
}