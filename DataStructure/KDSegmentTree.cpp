#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct KDSegmentTree{
    struct Node{
        T v; 
        int L, R;
        Node *l, *r;
        Node(int _L, int _R, const T& _v = 0) : v(_v){
            l = r = NULL;
            L = _L, R = _R;
        }
        inline int len() { return R - L; }
        inline int mid() { return (R + L) >> 1; }
    }*rt;
    int k;
    KDSegmentTree(int _k){
        
    }
};
int main(){

}
