#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
const int MAXN = 1e5 + 5;
const int MAXV = 1e5 + 5;
const int MAXQ = 1e6 + 5;
typedef pair<int, int> pii;
struct MO {
    struct Q {
        int l, r, id, b;
        Q(int _l, int _r, int _id, int _b) 
            : l(_l), r(_r), id(_id), b(_b) {}
        bool operator < (const Q &q) const {
            return b == q.b ? r < q.r : l < q.l;
        }
    };
    int qn, sqn;
    vector<int> data; vector<Q> qs;
    pii ans; int cnt[MAXV], val_cnt[MAXV];
    MO(vector<int> &_data, vector<pii> &_qs) : data(_data) {
        qn = _qs.size(), sqn = (int)(sqrt(qn) + 1e-6);
        for (int i = 0 ; i < _qs.size() ; i++)
            qs.emplace_back(_qs[i].F, _qs[i].S, i, _qs[i].F / sqn);
        ans = make_pair(0, 0);
        memset(  cnt  , 0, sizeof(  cnt  ));
        memset(val_cnt, 0, sizeof(val_cnt));
    }
    vector<pii> solve() {
        vector<pii> ret(qn);
        sort(qs.begin(), qs.end());
        int l = 0, r = 0;
        for (auto q : qs) {
            while (r < q.r) update(data[r++],  1);
            while (r > q.r) update(data[--r], -1);
            while (l > q.l) update(data[--l],  1);
            while (l < q.l) update(data[l++], -1);
            ret[q.id] = ans;
        }
        return ret;
    }
    void update(int num, int op) {
        if (op ==  1) {
            if (cnt[num]) val_cnt[cnt[num]]--;
            val_cnt[++cnt[num]]++;
            if (ans.F == cnt[num]) ans.S++;
            if (ans.F < cnt[num]) ans.F++, ans.S = 1;
        }
        if (op == -1) {
            val_cnt[cnt[num]]--;
            val_cnt[--cnt[num]]++;
            if (ans.F == cnt[num] + 1) 
                if (ans.S == 1) 
                    ans.F--, ans.S = val_cnt[cnt[num]];
                else ans.S--;
        }
    }
};
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> data(n);
    vector<pii> qs(q);
    for (auto &num : data) cin >> num;
    for (auto &p : qs) { cin >> p.F >> p.S; p.F--; }
    MO *sol = new MO(data, qs);
    vector<pii> ans = sol->solve();
    for (auto p : ans) cout << p.F << ' ' << p.S << '\n';
}
