#include <bits/stdc++.h>
using namespace std;
#define PB push_back
typedef long long LL;
struct SparseTable{
    vector<vector<LL> > data;
    LL (*op)(LL a, LL b);
    SparseTable(LL *arr, int n, LL (*_op)(LL a, LL b)){
        op = _op;
        int lgN = __lg(n) + 2;
        data.clear();
        data.resize(lgN);
        for (int i = 0 ; i < n ; i++) data[0].PB(arr[i]);
        for (int h = 1 ; h < lgN ; h++){
            int len = 1 << (h-1), i = 0;
            for (; i + len < n ; i++)
                data[h].PB(op(data[h-1][i], data[h-1][i+len]));
            if (!i) break;
            for (; i < n ; i++)
                data[h].PB(data[h-1][i]);
        }
    }
    int query(int l, int r){
        int h = __lg(r - l);
        int len = 1 << h;
        return op(data[h][l], data[h][r-len]);
    }
};
LL getMin(LL a, LL b){
    return a < b ? a : b;
}
LL getMax(LL a, LL b){
    return a > b ? a : b;
}
const int MAXN = 1e5 + 5;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    LL arr[MAXN];
    for (int i = 0 ; i < n ; i++) cin >> arr[i];
    SparseTable *minV = new SparseTable(arr, n, getMin);
    SparseTable *maxV = new SparseTable(arr, n, getMax);
    while (q--){
        int l, r; cin >> l >> r;
        cout << maxV->query(l-1, r) - minV->query(l-1, r) << '\n';
    }
    delete minV;
    delete maxV;
}
