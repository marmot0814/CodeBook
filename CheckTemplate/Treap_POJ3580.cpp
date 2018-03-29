#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
const int MAXN = 2e5 + 5;
typedef long long LL;
struct Treap{
    struct Node{
        Node *l, *r;
        int pri, sz;
        LL v, add, minV;
        bool rev;
        Node (LL _v = 0){
            v = _v;
            pri = rand();
            sz = 1;
            l = r = NULL;
            add = rev = 0;
            minV = v;
        }
        inline int size(){
            return this ? sz : 0;
        }
        inline void pull(){
            sz = 1 + l->size() + r->size();
            minV = v;
            if (l){
                l->push();
                minV = min(minV, l->minV);
            }
            if (r){
                r->push();
                minV = min(minV, r->minV);
            }
        }
        inline void push(){
            if (add){
                v += add;
                minV += add;
                if (l) l->add += add;
                if (r) r->add += add;
                add = 0;
            }
            if (rev){
                swap(l, r);
                if (l) l->rev ^= 1;
                if (r) r->rev ^= 1;
                rev = false;
            }
        }
    }*root, _mem[MAXN], *ptr;
    Treap(){
        ptr = _mem;
    }
    #define PNN pair<Node*, Node*>
    #define MP make_pair
    #define F first
    #define S second
    PNN split(Node *T, int x){
        if (!T) return MP((Node*)NULL, (Node*)NULL);
        T->push();
        if (T->l->size() < x){
            PNN tmp = split(T->r, x - T->l->size() - 1);
            T->r = tmp.F;
            T->pull();
            return MP(T, tmp.S);
        }else{
            PNN tmp = split(T->l, x);
            T->l = tmp.S;
            T->pull();
            return MP(tmp.F, T);
        }
    }
    Node* merge(Node *T1, Node *T2){
        if (!T1 || !T2) return T1 ? T1 : T2;
        if (T1->pri < T2->pri){
            T2->push();
            T2->l = merge(T1, T2->l);
            T2->pull();
            return T2;
        }else{
            T1->push();
            T1->r = merge(T1->r, T2);
            T1->pull();
            return T1;
        }
    }
    void insert(LL v, int k = -1){
        if (!~k) k = root->size() + 1;
        PNN tmp = split(root, k);
        root = merge(merge(tmp.F, new (ptr++)Node(v)), tmp.S);
    }
    void addValue(int x, int y, LL v){
        PNN tmp_1 = split(root, y);
        PNN tmp_2 = split(tmp_1.F, x - 1);
        tmp_2.S->add += v;
        root = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
    }
    void earse(int k){
        PNN tmp_1 = split(root, k);
        PNN tmp_2 = split(tmp_1.F, k-1);
        root = merge(tmp_2.F, tmp_1.S);
    }
    int minValue(int x, int y){
        PNN tmp_1 = split(root, y);
        PNN tmp_2 = split(tmp_1.F, x - 1);
        LL res = tmp_2.S->minV;
        root = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
        return res;
    }
    void reverse(int x, int y){
        PNN tmp_1 = split(root, y);
        PNN tmp_2 = split(tmp_1.F, x - 1);
        tmp_2.S->rev ^= 1;
        root = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
    }
    void revolve(int x, int y, int t){
        PNN tmp_1 = split(root, y);
        PNN tmp_2 = split(tmp_1.F, x - 1);
        int len = y - x + 1;
        t %= len;
        PNN tmp_3 = split(tmp_2.S, len - t);
        tmp_2.S = merge(tmp_3.S, tmp_3.F);
        root = merge(merge(tmp_2.F, tmp_2.S), tmp_1.S);
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    Treap *sol = new Treap();
    for (int i = 0 ; i < n ; i++){
        LL tmp; cin >> tmp;
        sol->insert(tmp);
    }
    int q; cin >> q;
    while (q--){
        char op[10]; cin >> op;
        int x, y;
        LL k;
        switch(op[0]){
            case 'A':
                cin >> x >> y >> k;
                sol->addValue(x, y, k);
                break;
            case 'R':
                if (op[3] == 'E'){
                    cin >> x >> y;
                    sol->reverse(x, y);
                }
                if (op[3] == 'O'){
                    cin >> x >> y >> k;
                    sol->revolve(x, y, k);
                }
                break;
            case 'I':
                cin >> x >> k;
                sol->insert(k, x);
                break;
            case 'D':
                cin >> x;
                sol->earse(x);
                break;
            case 'M':
                int x, y; cin >> x >> y;
                cout << sol->minValue(x, y) << '\n';
                break;
        }
    }
    delete sol;
}
