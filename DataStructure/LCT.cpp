#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
struct LCT{
    const int L = 0, R = 1;
    struct Node{
        Node *ch[2], *pa;
        bool rev;
        Node(){ rev = false, ch[0] = ch[1] = pa = NULL; }
    }_mem[MAXN], *ptr;
    LCT(){
        ptr = _mem;
    }
    void rotate(){
    }
    void splay(){

    }
};
int main(){

}
