#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
using T = double;
const double EPS = 1e-9;
struct P {
    T x, y; P(T _x=0.0,T _y=0.0):x(_x),y(_y){}
    P operator+(const P&p){return P(x+p.x,y+p.y);}
    P operator-(const P&p){return P(x-p.x,y-p.y);}
    T operator*(const P&p){return x*p.x+y*p.y;}
    T operator%(const P&p){return x*p.y-y*p.x;}
    P operator*(const T c){return P(c*x,c*y);}
    T len(){return sqrt(*this**this);}
    bool operator<(const P&p)const{
        return MP(x,y)<MP(p.x,p.y);
        // return atan2(x,y)<atan2(p.x,p.y);
    }
};
typedef P V;
struct L {
    P p1, p2;
    L(P _p1,P _p2):p1(_p1), p2(_p2){}
    V getV(){return p1-p2;}
};
typedef L S;

