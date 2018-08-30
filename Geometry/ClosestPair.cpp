#include "Point.cpp"
using namespace std;
const double INF = 0x3f3f3f3f;
bool cmpx(P a, P b) { return a.x < b.x; }
bool cmpy(P a, P b) { return a.y < b.y; }
pair<P, P> DnC(vector<P> &p, int L, int R) {
    if (R - L <= 1) return make_pair(P(-INF, -INF), P(INF, INF));
    int M = (L + R) >> 1;
    pair<P, P> l = DnC(p, L, M);
    pair<P, P> r = DnC(p, M, R);
    

}
pair<P, P> closestPair(vector<P> &p) {
    sort(p.begin(), p.end(), cmpx);
    return DnC(p, 0, p.size());
}
int main() {

}
