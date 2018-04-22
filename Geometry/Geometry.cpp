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
    Point (double _x = 0, double _y = 0) : x(_x), y(_y) {}
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator * (double p) const { return Point(x * p, y * p); }
    double operator * (const Vector& v) const { return x * v.x + y * v.y; }
    Point operator / (double p) const { return Point(x / p, y / p); }
    double operator ^ (const Vector& v) const { return x * v.y - y * v.x; }
    bool operator == (const Point& p) const { return !dcmp(x - p.x) && !dcmp(y - p.y); }
};
int main(){

}
