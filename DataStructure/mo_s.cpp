#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXQ = 1e5 + 5;
typedef pair<int, int> pii; 
struct MO {
    struct Q {
        int l, r, b, id;
        Q(int _l, int _r, int _id, int _b) {
            l = _l, r = _r, id = _id, b = _b;
        }
        bool operator < (const Q &q) const {
            return b == q.b ? r < q.r : l < q.l;
        }
    };
    vector<Q> q; vector<int> data;
    int qn, sqn;
    int ans = 0; set<pii> sort_cnt; map<int, int> cnt;  // F: cnt, S: num
    MO(vector<int> &_data, vector<pii> &_q) : data(_data) {
        qn = _q.size(), sqn = (int)(sqrt(qn) + 1e-6);
        for (int i = 0 ; i < _q.size() ; i++) {
            Q input(_q[i].F, _q[i].S, i, _q.size() / sqn);
            q.push_back(input);
        }
        ans = 0;
    }
    void pull(int num, int op) {
        if (op ==  1) {
            sort_cnt.erase(make_pair(cnt[num], num));
            cnt[num]++;
            sort_cnt.insert(make_pair(cnt[num], num));
        }
        if (op == -1) {
            sort_cnt.erase(make_pair(cnt[num], num));
            cnt[num]--;
            if (cnt[num]) sort_cnt.insert(make_pair(cnt[num], num));
        }
        ans = sort_cnt.rbegin()->S;
    }
    vector<int> solve() {
        vector<int> ret(qn);
        sort(q.begin(), q.end());
        int l = 0, r = 0;
        for (auto qu : q) {
            while (r < qu.r) pull(data[r++],  1);
            while (r > qu.r) pull(data[--r], -1);
            while (l > qu.l) pull(data[--l],  1);
            while (l < qu.l) pull(data[l++], -1);
            ret[qu.id] = ans;
        }
        return ret;
    }
};
int main() {
    int n, m; while (cin >> n >> m) {
        vector<int> data;
        for (int i = 0 ; i < n ; i++) {
            int input; cin >> input;
            data.push_back(input);
        }
        vector<pii> q;
        while (m--) {
            int l, r; cin >> l >> r;
            q.push_back(make_pair(l, r));
        }
        MO *sol = new MO(data, q);
        vector<int> ans = sol->solve();
        for (int i = 0 ; i < ans.size() ; i++) {
            cout << ans[i] << '\n';
        }
        delete sol;
    }
}
