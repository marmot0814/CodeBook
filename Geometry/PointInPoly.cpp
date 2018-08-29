#include "Point.cpp"
using namespace std;
double interpolate_x(double y, P p1, P p2) {
    if (p1.y == p2.y) return p1.x;
    return p1.x + (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
}
bool PinPs(vector<P> &ps, P p) {
    bool c = false;
    for (int i = ps.size() - 1, j = 0; j < ps.size() ; i = j++)
        if ((ps[i].y > p.y) != (ps[j].y > p.y) && p.x < interpolate_x(p.y, ps[i], ps[j]))
            c = !c;
    return c;
}
int main() {

}
