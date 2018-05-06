#include <bits/stdc++.h>
using namespace std;
const int SIGMA = 26;
struct SAM {
    struct Node {
        Node *f, *ch[SIGMA];
        int len;
        Node(int _len) {
            len = _len; f = 0;
            memset(ch, 0, sizeof(ch));
        }
    }*rt, *la;
    char *s;
    inline int idx(char c) { return c - 'a'; }
    SAM(char *_s) { s = _s;
        rt = la = new Node(0);
        for (int i = 0 ; s[i] ; i++) extend(idx(s[i]));
    }
    ~SAM() {
        Node *u = rt; int i = 0;
        while (u) {
            Node *next = u->ch[idx(s[i++])];
            delete u; u = next;
        }
    }
    void extend(int c) {
        Node *u = la; la = new Node(la->len + 1);
        for (; u && !u->ch[c] ; u = u->f) u->ch[c] = la;
        if (!u) la->f = rt;
        else {
            Node *pf = u->ch[c];
            if (pf->len == u->len + 1) la->f = pf;
            else {
                Node *cn = new Node(u->len + 1);
                for (; u && u->ch[c] == pf; u = u->f) u->ch[c] = cn;
                for (int i = 0 ; i < SIGMA ; i++) cn->ch[i] = pf->ch[i];
                cn->f = pf->f;
                pf->f = la->f = cn;
            }
        }
    }
    int search(char *s) {
        Node *u = rt; int ans = 0;
        for (int i = 0 ; s[i] ; i++) {
            u = u->ch[idx(s[i])];
            if (u == rt) ans++;
            if (!u) return 0;
        }
        return ans;
    }
};
const int MAXLEN = 1e4 + 5;
int main() {
    int t; cin >> t; while (t--) {
        char s[MAXLEN]; cin >> s;
        SAM *sol = new SAM(s);
        int m; cin >> m;
        while (m--) {
            char target[MAXLEN]; cin >> target;
            cout << sol->search(target) << '\n';
        }
        delete sol;
    }
}
