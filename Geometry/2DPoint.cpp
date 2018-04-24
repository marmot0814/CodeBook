#include <bits/stdc++.h>
using namespace std;
#define MP make_pair
struct Point {
    double x, y;
    Point (double _x = 0, double _y = 0) : x(_x), y(_y) {}
    bool operator < (const Point &p) const {
        // return MP(x, y) < MP(p.x, p.y);
        // return atan2(y, x), atan2(p.y, p.x);
    }
    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator * (const double &d) const {
        return Point(d * x, d * y);
    }
    double operator * (const Point &p) const {
        return x * p.x + y * p.y;
    }
    double operator % (const Point &p) const {
        return x * p.y - y * p.x;
    }
    friend double abs2(const Point &p) {
        return p * p;
    }
    friend double abs(const Point &p) {
        return sqrt(abs(p));
    }
};
typedef Point Vector;
struct Line {
    Point p; Vector v;
    bool operator < (const Line &l) const {
        return atan2(v.y, v.x) < atan2(l.v.y, l.v.x);
    }
};
int main() {

}
