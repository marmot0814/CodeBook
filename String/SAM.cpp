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
    inline int idx(char c) { return c - 'a'; }
    SAM(char *s) {
        rt = la = new Node(0);
        for (int i = 0 ; s[i] ; i++) extend(idx(s[i]));
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
    bool search(char *s) {
        Node *u = rt;
        for (int i = 0 ; s[i] ; i++) {
            u = u->ch[idx(s[i])];
            if (!u) return false;
        }
        return true;
    }
};
const int MAXLEN = 1e5 + 5;
int main() {

}
