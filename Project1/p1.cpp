#include <bits/stdc++.h>
#define ll long long

ll read() {
    ll x=0, f=1; int ch=getchar();
    for (; ch<'0' || ch>'9'; ch=getchar()) if (ch=='-') f=-1;
    for (; ch>='0' && ch<='9'; ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

class Point
{
private:
public:
    ll x;
    ll y;
    Point(ll _x, ll _y): x(_x), y(_y) {}
    ~Point() {}
};

ll ccw(Point a, Point b, Point c) {
    return (ll)(b.x - a.x) * (ll)(c.y - a.y) - (ll)(b.y - a.y) * (ll)(c.x - a.x);
}

void GrahamsScan(std::vector<Point> X) {
    if (X.empty()) return;
    Point p0 = X[0];
    for (auto p: X) 
        if (p.y < p0.y || (p.y == p0.y && p.x < p0.x)) 
            p0 = p;
    std::sort(X.begin(), X.end(), [p0](Point a, Point b) {
        if (a.x == p0.x && a.y == p0.y) return true;
        if (b.x == p0.x && b.y == p0.y) return false;
        return ccw(p0, a, b) > 0;
    });
    std::vector<Point> stk{p0};

    for (auto p: X) {
        if (p.x == p0.x && p.y == p0.y) continue;
        while (stk.size() > 1 && ccw(stk[stk.size() - 2], stk[stk.size() - 1], p) <= 0) 
            stk.pop_back();
        stk.push_back(p);
    }
    for (auto p: stk) 
        std::cout << p.x << " " << p.y << std::endl;
    return;
}

int main() {
    int n = (int)read();
    std::vector<Point> X;
    for (int i = 0; i < n; i++) {
        ll x = read(), y = read();
        X.emplace_back(x, y);
    }
    GrahamsScan(X);
    return 0;
}