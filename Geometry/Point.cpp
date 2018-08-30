#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
using T = double;
const double EPS = 1e-9;
int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}
struct P {
    T x, y; P(T _x=0.0,T _y=0.0):x(_x),y(_y){}
    P operator+(const P&p){return P(x+p.x,y+p.y);}
    P operator-(const P&p){return P(x-p.x,y-p.y);}
    T operator*(const P&p){return x*p.x+y*p.y;}
    T operator%(const P&p){return x*p.y-y*p.x;}
    P operator*(const T c){return P(x*c,y*c);}
    P operator/(const T c){return P(x/c,y/c);}
    bool operator == (const P &p){
        return dcmp(x - p.x) == 0 && dcmp(y - p.y);
    }
    bool operator<(const P&p)const{
        return MP(x,y)<MP(p.x,p.y);
        // return atan2(x,y)<atan2(p.x,p.y);
    }
    T len(){return sqrt(*this**this);}
    T operator^(P&p){return acos(*this*p/len()/p.len());}
    P normal() { return P(-y, x)/len(); }
    P rotate(double rad) {
        return P(x*cos(rad)-y*sin(rad), x*sin(rad)+y*cos(rad));
    }
};
T area(P a, P b, P c) {
    return (a - b) % (a - c) / 2.0;
}
typedef P V;
struct L {
    P p1, p2;
    L(P _p1,P _p2):p1(_p1), p2(_p2){}
    V getV(){return p1-p2;}
};
P LLintersect(L: l1, L l2) {
    assert(dcmp(l1.getV() % l2.getV()) != 0);
    return l1.p1 + l1.getV() * (l2.getV() % (l1.p1 - l2.p1)) / (l1.getV() % l2.getV());
}
typedef L S;
