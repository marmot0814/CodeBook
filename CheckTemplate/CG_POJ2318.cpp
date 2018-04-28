#include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 5e3 + 5;
struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    int operator % (const Point &p) const {
        return x * p.y - y * p.x;
    }
    friend ostream& operator << (ostream& out, const Point &p) {
        out << "(" << p.x << ',' << p.y << ")";
        return out;
    }
}toyz[MAXN];
struct Line {
    Point p1, p2;
    Line() {}
    Line(const Point &_p1, const Point &_p2) : p1(_p1), p2(_p2){}
    friend ostream& operator << (ostream& out, const Line &l) {
        out << l.p1 << ' ' << l.p2;
        return out;
    }
}line[MAXN];
bool check(const Point &p, const Line &l) {
    return (l.p1 - l.p2) % (p - l.p2) > 0;
}
int main() {
    int n; while (cin >> n && n) {
        int m; cin >> m;
        int x_1, y_1, x_2, y_2;
        cin >> x_1 >> y_1 >> x_2 >> y_2;
        for (int i = 1 ; i <= n ; i++) {
            cin >> line[i].p1.x >> line[i].p2.x;
            line[i].p1.y = y_1; line[i].p2.y = y_2;
        }
        line[0].p1 = Point(x_1, y_1);
        line[0].p2 = Point(x_1, y_2);
        line[n+1].p1 = Point(x_2, y_1);
        line[n+1].p2 = Point(x_2, y_2);
        int cnt[MAXN]; memset(cnt, 0, sizeof(cnt));
        for (int i = 0 ; i < m ; i++) {
            cin >> toyz[i].x >> toyz[i].y;
            int L = 0, R = n + 1;
            while (R - L > 1) {
                int M = (R + L) >> 1;
                if (check(toyz[i], line[M])) {
                    R = M;
                } else {
                    L = M;
                }
            }
            cnt[L]++;
        }
        for (int i = 0 ; i <= n ; i++) 
            cout << i << ": " << cnt[i] << '\n';
        cout << '\n';
    }
}
