#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
using T = double;
struct P {
    T x, y; P(T _x=0,T _y=0):x(_x),y(_y){}
    P operator+(const P&p){return P(x+p.x,y+p.y);}
    P operator-(const P&p){return P(x-p.x,y-p.y);}
    T operator*(const P&p){return x*p.x+y*p.y;}
    T operator%(const P&p){return x*p.y-y*p.x;}
    P operator*(const T c){return P(c*x,c*y);}        
};
struct L {
    P p1, p2;
    L(P _p1,P _p2):p1(_p1), p2(_p2){}
    V getV(){return p1-p2;}
};
typedef P V;
typedef L S;
bool PSinter(P p, S s) {
    V v1=p-s.p1,v2=p-s.p2;
    return (v1%v2==0)&&(v1*v2<= 0);
}
bool SSinter(S s1,S s2) {
    T c1=s1.getV()%(s1.p1-s2.p1);
    T c2=s1.getV()%(s1.p1-s2.p2);
    T c3=s2.getV()%(s2.p1-s1.p1);
    T c4=s2.getV()%(s2.p1-s1.p2);
    if (c1*c2<0&&c3*c4<0)return true;
    if (c1==0&&PSinter(s2.p1,s1))return true;
    if (c2==0&&PSinter(s2.p2,s1))return true;
    if (c3==0&&PSinter(s1.p1,s2))return true;
    if (c4==0&&PSinter(s1.p2,s2))return true;
    return false;
}
int main() {
    int t; cin >> t; while (t--) {
        P p[4]; for (int i = 0 ; i < 4 ; i++) cin >> p[i].x >> p[i].y;
        cout << (SSinter(S(p[0], p[1]), S(p[2], p[3])) ? "Yes\n" : "No\n");
    }
}
