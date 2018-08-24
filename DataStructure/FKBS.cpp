#include <bits/stdc++.h>
using namespace std;
struct FKBS {
    vector<int> data, mdata;
    int n, BASE;
    FKBS(vector<int> &_data) : data(_data) {
        n = data.size();
        BASE = (int)(sqrt(n) + 1e-6);
        mdata.resize(BASE);
        for (int i = 0 ; i < BASE ; i++)
            for (int j = 0 ; j < BASE ; j++)
                mdata[i] = max(mdata[i], data[i * BASE + j]);
    }
    int getMax(int l, int r) {
        int ret = 0;
        for (int b = 0, i = 0; b < r ; i++, b += BASE) {
            if (b + BASE <= l || r <= b) continue;
            if (l <= b && b + BASE <= r) ret = max(ret, mdata[i]);
            else for (int j = 0 ; j < BASE ; j++) {
                int idx = b + j;
                if (l <= idx & idx < r)
                    ret = max(ret, data[idx]);
            }
        }
        return ret;
    }
};
int main() {
    int n; cin >> n; vector<int> data;
    for (int i = 0 ; i < n ; i++) {
        int input; cin >> input;
        data.push_back(input);
    }
    FKBS *sol = new FKBS(data);
    int l, r; while (cin >> l >> r) {
        cout << sol->getMax(l ,r) << '\n'; 
    }
    delete sol;
}
