#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-8;
const double PI  = acos(-1.0);
int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    else return x < 0 ? -1 : 1;
}
struct Point{
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator * (const double& b) const {
        return Point(x * b, y * b);
    }
    Point operator / (const double& b) const {
        return Point(x / b, y / b);
    }
    bool operator == (const Point &p) const {
        return !dcmp(x - p.x) && !dcmp(y - p.y);
    }
    double operator * (const Point &p) const {
        return x * p.x + y * p.y;
    }
    double operator % (const Point &p) const {
        return x * p.y - y * p.x;
    }
    Point normal() {
        return Point(-y, x) / len();
    }
    double len2() {
        return (*this) * (*this);
    }
    double len() {
        return sqrt(len2());
    }
    bool operator < (const Point &p) {
        return dcmp(x - p.x) ? dcmp(x - p.x) == -1 : dcmp(y - p.y) == -1;
    }
    double angle() const {
        double A = atan2(y, x);
        if (A <= -PI / 2) A += PI * 2;
        return A;
    }
    friend ostream& operator << (ostream &out, const Point &p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
};
struct Line {
    Line(){}
    Point p1, p2;
    double a, b, c;
    Line(const Point &_p1, const Point &_p2) : p1(_p1), p2(_p2) {}
    void pton() {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = - a * p1.x - b * p1.y;
    }
    double operator % (const Point &p) const {
        return (p2 - p1) % (p - p1);
    }
    bool point_on_segment(const Point &p) const {
        return !dcmp(*this % p) && dcmp((p1 - p) * (p2 - p)) <= 0;
    }
    double dis2(const Point &p, bool is_segment = false) const {
        Point v = p2 - p1, v1 = p - p1;
        if (is_segment) {
            Point v2 = p - p2;
            if (dcmp(v * v1) <= 0) return v1.len2();
            if (dcmp(v * v2) >= 0) return v2.len2();
        }
        double tmp = v % v1;
        return tmp * tmp / v.len2();
    }
    double seg_dis2(const Line &l) const {
        return min({dis2(l.p1, true), dis2(l.p2, true), dis2(p1, true), dis2(p2, true)});
    }
    Point projection(const Point &p) const {
        Point n = (p2 - p1).normal();
        return p - n * ((p - p1) * n) / n.len2();
    }
    Point mirror(const Point &p) {
        Point R; pton();
        double d = a * a + b * b;
        R.x = (b * b * p.x - a * a * p.x - 2 * a * b * p.y - 2 * a * c) / d;
        R.y = (a * a * p.y - b * b * p.y - 2 * a * b * p.x - 2 * b * c) / d;
        return R;
    }
    bool equel(const Line &l) const {
        return dcmp(*this % l.p1) == 0 && dcmp(*this % l.p2) == 0;
    }
    bool parallel(const Line &l) const {
        return dcmp((p1 - p2) % (l.p1 - l.p2)) == 0;
    }
    bool cross_seg(const Line &l) const {
        return dcmp(((p2 - p1) % (l.p1 - p1)) * ((p2 - p1) % (l.p2 - p1))) <= 0;
    }
};
int main() {
    Line l(Point(0, 1), Point(1, 0)); Point p(7, 3);
    Line l2(Point(1, 1), Point(0, 0));
    cout << l.cross_seg(l2) << '\n';
}
