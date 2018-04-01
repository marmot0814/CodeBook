#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-10;
int dcmp(double x){
    if (fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}
struct Point{
    double x, y;
    Point (double x = 0, double y = 0) : x(x), y(y){}
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double p) const { return Point(x * p, y * p); }
    Point operator / (double p) const { return Point(x / p, y / p); }
    bool operator == (const Point& p) { return !dcmp(x - p.x) && !dcmp(y - p.y); }
    double dot (const Point& p) const { return x * p.x + y * p.y; }
    double len() const { return sqrt(dot(*this)); }
    double angle (const Point& p) const { return acos(dot(p) / len() / p.len()); }
    double cross (const Point& p) const { return x * p.y - y * p.x; }
    double area (const Point& p1, const Point& p2) const { return (p1-*this).cross(p2-*this); }
    Point rotate(double rad) const { return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)); }
    Point normal() const { double L = len(); return L ? Point(-y / L, x / L) : *this; }
};
int main(){

}
