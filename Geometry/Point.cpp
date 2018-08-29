#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
const int INF = 0x3f3f3f3f;
using T = double;
struct P {
    T x, y; P(T _x=0,T _y=0):x(_x),y(_y){}
    P operator+(const P&p){return P(x+p.x,y+p.y);}
    P operator-(const P&p){return P(x-p.x,y-p.y);}
    T operator*(const P&p){return x*p.x+y*p.y;}
    T operator%(const P&p){return x*p.y-y*p.x;}
    P operator*(const T c){return P(c*x,c*y);}        
    bool operator < (const P &p) const {
        // return MP(x, y) < MP(p.x, p.y);
        // return atan2(y, x), atan2(p.y, p.x);
    }
    double len() { return sqrt(*this * *this); }
};
typedef P V;
struct L {
    P p1, p2;
    L(P _p1, P _p2):p1(_p1), p2(_p2){}
};
typedef L S;
double P_to_P_dist(P p1,P p2){return (p1-p2).len();}
double P_to_L_dist(P p, L l) {
    V v1 = p - l.p1, v2 = l.p2 - l.p1;
    return fabs(v1 % v2) / v2.len();
}
double P_to_S_dist(P p, S s) {
    V v = s.p2 - s.p1;
    V v1 = p - s.p1;
    V v2 = p - s.p2;
    if (v * v1 <= 0) return v1.len();
    if (v * v2 >= 0) return v2.len();
    return fabs(v % v1) / v.len();
}
bool S_to_S_intersect(S s1, S s2);
double S_to_S_dist(S s1, S s2) {
    if (S_to_S_intersect(s1, s2)) return 0;
    return min({
        P_to_S_dist(s1.p1, s2),
        P_to_S_dist(s1.p2, s2),
        P_to_S_dist(s2.p1, s1),
        P_to_S_dist(s2.p2, s1)
    });
}
double L_to_L_dist(L l1, L l2) {
    V v1 = l1.p2 - l1.p1;
    V v2 = l2.p2 - l2.p1;
    if (v1 % v2 != 0) return 0;
    return P_to_L_dist(l1.p1, l2);
}
bool P_to_S_intersect(P p, S s) {
    V v1 = p - s.p1, v2 = p - s.p2;
    return v1 % v2 == 0
        && v1 * v2 <= 0;
}
bool S_to_S_intersect(S s1, S s2) {
    T c1 = (s1.p1 - s1.p2) % (s1.p1 - s2.p1);
    T c2 = (s1.p1 - s1.p2) % (s1.p1 - s2.p2);
    T c3 = (s2.p1 - s2.p2) % (s2.p1 - s1.p1);
    T c4 = (s2.p1 - s2.p2) % (s2.p1 - s1.p2);
    // 端點不共線
    if (c1 * c2 < 0 && c3 * c4 < 0) return true;
    // 端點共線
    if (c1 == 0 && P_to_S_intersect(s1.p1, S(s1.p2, s2.p1))) return true;
    if (c2 == 0 && P_to_S_intersect(s1.p1, S(s1.p2, s2.p2))) return true;
    if (c3 == 0 && P_to_S_intersect(s2.p1, S(s2.p2, s1.p1))) return true;
    if (c4 == 0 && P_to_S_intersect(s2.p1, S(s2.p2, s1.p2))) return true;
    return false;
}
P L_to_L_intersection(L l1, L l2) {
    P a = l1.p2 - l1.p1, b = l2.p2 - l2.p1, s = l2.p1 - l1.p1;
    if (a % b == 0) return P(INF, INF);
    return l1.p1 + a * ((s % b) / (a % b));
}
int main() {
    P p1(3, 5), p2(3, 6);
    cout << (p1 < p2) << '\n';
}
