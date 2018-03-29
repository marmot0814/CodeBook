#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-8;
template <typename T>
inline char cmp(const T& a, const T& b){
    if (abs(a - b) < EPS) return 0;
    if (a - b < -EPS) return -1;
    if (b - a < -EPS) return 1;
}
template <typename T> 
struct Point{
    T x, y; Point(){}
    Point(const T& x, const T& y) : x(x), y(y){}
    Point operator + (const Point& b)const{
        return Point(x + b.x, y + b.y);
    }
    Point operator - (const Point& b)const{
        return Point(x - b.x, y - b.y);
    }
    Point operator * (const T& b)const{
        return Point(x * b, y * b);
    }
    Point operator / (const T& b)const{
        return Point(x / b.x, y / b.y);
    }
    bool operator == (const Point &b)const{
        return !cmp(x, x.b) && !cmp(y, y.b);
    }
    T dot(const Point& b)const {
        return x * b.x + y * b.y;
    }
    T cross(const Point& b)const{
        return x * b.y - y * b.x;
    }
    Point normal()const{
        return Point(-y, x);
    }
    Point len()const{
        return dot * (*this);
    }
    T rad(const Point& b)const{
        return fabs(atan2(fabs(cross(b)), dot(b)));
    }
    T getA(){

    }
};
int main(){
}
