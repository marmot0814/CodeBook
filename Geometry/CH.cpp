#include "Point.cpp"
using namespace std;
vector<P> CH(vector<P> &ps) {   // front() back() is same
    sort(ps.begin(), ps.end());
    vector<P> ret; int m = 0;
    for (int i = 0 ; i < ps.size() ; i++) {
        while (m >= 2 && (ps[i] - ret[m - 2]) % (ret[m -1] - ret[m - 2]) < -EPS) ret.pop_back(), m--;
        ret.push_back(ps[i]), m++;
    }
    for (int i = ps.size() - 2 ; ~i ; i--) {
        while (m >= 2 && (ps[i] - ret[m - 2]) % (ret[m - 1] - ret[m - 2]) < -EPS) ret.pop_back(), m--;
        ret.push_back(ps[i]); m++;
    }
    return ret;
}
int main() {

}
