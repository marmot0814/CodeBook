#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-10;
int dcmp(double x){
    if (fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}
struct Point{
    typedef Point Vector;
    double x, y;
    Point (double x = 0, double y = 0) : x(x), y(y){}
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double p) const { return Point(x * p, y * p); }
    double operator * (const Vector& v) const { return x * v.x + y * v.y; }
    Point operator / (double p) const { return Point(x / p, y / p); }
    double operator ^ (const Vector& v) const { return x * v.y - y * v.x; }
    bool operator == (const Point& p) { return !dcmp(x - p.x) && !dcmp(y - p.y); }
    double len() const { return sqrt(*this * *this); }
    Vector rotate(double rad) const { return Vector(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)); }
    Vector normal() { return len() ? Vector(-y, x) / len() : *this; }
    friend ostream& operator << (ostream& out, const Point& p){
        out << "(" << p.x << "," << p.y << ")";
        return out;
    }
};
typedef Point Vector;
double angle(const Vector& v1, const Vector& v2) { return acos(v1 * v2 / v1.len() / v2.len()); }
double area(const Point& p1, const Point& p2, const Point& p3) { return (p2 - p1) ^ (p3 - p1) / 2.0; }
struct Line{
    Point p; Vector v;
    Line(const Point& p, const Vector& v) : p(p), v(v){}
};
struct Segment{
    Point p1, p2;
    Segment(const Point& p1, const Point& p2) : p1(p1), p2(p2){}
};
Point LineIntersection(const Line& l1, const Line& l2) {
    Vector u = l1.p - l2.p;
    assert(dcmp(l1.v ^ l2.v));
    double t = (l2.v ^ u) / (l1.v ^ l2.v);
    return l1.p + l1.v * t;
}
double PointLineDist(const Point& p, const Line& l){
    Vector _v = p - l.p;
    return fabs(l.v ^ _v / l.v.len());
}
double PointSegmentDist(const Point& p, const Segment& s){
    if (Point(s.p1) == s.p2) return (s.p1 - p).len();
    Vector v1 = s.p2 - s.p1, v2 = p - s.p1, v3 = p - s.p2;
    if (dcmp(v1 * v2) < 0) return v2.len();
    if (dcmp(v1 * v3) > 0) return v3.len();
    return fabs(v1 ^ v2) / v1.len();
}
Point PointLineProject(const Point& p, const Line& l){
    return l.p + l.v * (l.v * (p - l.p)) / (l.v * l.v);
}
bool SegmentProperIntersection(const Segment& s1, const Segment& s2){
    double c1 = (s1.p2 - s1.p1) ^ (s2.p1 - s1.p1), c2 = (s1.p2 - s1.p1) ^ (s2.p2 - s1.p1),
           c3 = (s2.p2 - s2.p1) ^ (s1.p1 - s2.p1), c4 = (s2.p2 - s2.p1) ^ (s1.p2 - s2.p1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
bool OnSegment(const Point& p, const Segment& s){
    return dcmp((s.p1 - p) ^ (s.p2 - p)) == 0 && dcmp((s.p1 - p) * (s.p2 - p)) < 0;
}
double PolygonArea(Point *p, int n){
    double area = 0;
    for (int i = 1 ; i < n-1 ; i++)
        area += (p[i] - p[0]) ^ (p[i+1] - p[0]);
    return fabs(area) / 2.0;
}
int main(){
    Point p[4];
    p[0] = Point(-3, 5);
    p[1] = Point(2, 3);
    p[2] = Point(6, 7);
    p[3] = Point(2, 0);
    cout << fixed << setprecision(15) << PolygonArea(p, 4) << '\n';
}
