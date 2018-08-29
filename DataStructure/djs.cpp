#include <bits/stdc++.h>
using namespace std;
struct djs {
    vector<int> pa; int n;
    djs(int _n) : n(_n) { pa.resize(n, -1); }
    int find(int x) { return pa[x] < 0 ? x : pa[x] = find(pa[x]); }
    bool Union(int u, int v) {
        int x = find(u), y = find(v);
        if (x == y) return false;
        if (pa[x] < pa[y]) swap(x, y);
        pa[y] += pa[x], pa[x] = y;
        return true;
    }
};
int main() {

}
