#include "Point.cpp"
using namespace std;
bool PSinter(P p, S s) {
    V v1=p-s.p1,v2=p-s.p2;
    return (fabs(v1%v2)<EPS)&&(v1*v2<=EPS);
}
bool SSinter(S s1, S s2) {
    T c1 = s1.getV() % (s1.p1 - s2.p1);
    T c2 = s1.getV() % (s1.p1 - s2.p2);
    T c3 = s2.getV() % (s2.p1 - s1.p1);
    T c4 = s2.getV() % (s2.p1 - s1.p2);
    if (dcmp(c1 * c2) < 0 && dcmp(c3 * c4) < 0)return true;
    if (dcmp(c1) == 0 && PSinter(s2.p1, s1))return true;
    if (dcmp(c2) == 0 && PSinter(s2.p2, s1))return true;
    if (dcmp(c3) == 0 && PSinter(s1.p1, s2))return true;
    if (dcmp(c4) == 0 && PSinter(s1.p2, s2))return true;
    return false;
}
int main() {
    
}
