#include <bits/stdc++.h>
using namespace std;
const int MAXN = 35;
bool G[MAXN][MAXN];
struct Set { 
    bool s[MAXN]; int size; 
    Set() { memset(s, false, sizeof(s)); size = 0; }
};
int n, m, maximum_clique;
Set intersect(Set S, int u) {
    for (int i = 0 ; i < n ; i++) {
        if (S.s[i] && !G[u][i]) {
            S.s[i] = false;
            S.size--;
        }
    }
    return S;
}
void backtrack(Set R, Set P, Set X) {
    if (P.size == 0) {
        if (X.size == 0) {
            maximum_clique = max(maximum_clique, R.size);
        }
        return ;
    }
    int pivot;
    for (pivot = 0 ; pivot < n ; pivot++) 
        if (P.s[pivot] || X.s[pivot])
            break;
    for (int i = 0 ; i < n ; i++) {
        if (P.s[i] && !G[pivot][i]) {
            R.s[i] = true; R.size++;
            backtrack(R, intersect(P, i), intersect(X, i));
            R.s[i] = false; R.size--;
            P.s[i] = false; P.size--;
            if (!X.s[i]) X.s[i] = true, X.size++;
        }
    }
}
void BK() {
    for (int i = 0 ; i < n ; i++) G[i][i] = false;
    Set R, P, X;
    for (int i = 0 ; i < n ; i++) R.s[i] = false;
    for (int i = 0 ; i < n ; i++) P.s[i] = true;
    for (int i = 0 ; i < n ; i++) X.s[i] = false;
    R.size = 0;
    P.size = n;
    X.size = 0;
    backtrack(R, P, X);
}
int main() {
    while (cin >> n >> m) {
        memset(G, false, sizeof(G));
        maximum_clique = 0;
        for (int i = 0 ; i < m ; i++) {
            int u, v; cin >> u >> v;
            G[u][v] = G[v][u] = true;
        }
        BK();
        cout << maximum_clique << '\n';
    }
}
