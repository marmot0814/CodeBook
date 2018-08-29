#include "Point.cpp"
using namespace std;
bool PSinter(P p, S s) {
    V v1=p-s.p1,v2=p-s.p2;
    return (fabs(v1%v2)<EPS)&&(v1*v2<=EPS);
}
bool SSinter(S s1,S s2) {
    T c1=s1.getV()%(s1.p1-s2.p1);
    T c2=s1.getV()%(s1.p1-s2.p2);
    T c3=s2.getV()%(s2.p1-s1.p1);
    T c4=s2.getV()%(s2.p1-s1.p2);
    if (c1*c2<-EPS&&c3*c4<-EPS)return true;
    if (fabs(c1)<EPS&&PSinter(s2.p1,s1))return true;
    if (fabs(c2)<EPS&&PSinter(s2.p2,s1))return true;
    if (fabs(c3)<EPS&&PSinter(s1.p1,s2))return true;
    if (fabs(c4)<EPS&&PSinter(s1.p2,s2))return true;
    return false;
}
int main() {

}
