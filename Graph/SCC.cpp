#include <bits/stdc++.h>
using namespace std;
struct Graph{
    struct Node; struct Edge;
    int V;
    struct Node : vector<Edge*> {
        
    }_memN[MAXN], *node[MAXN];
    struct Edge{
        Node *v;

    }_memE[MAXM], *ptrE;
    Graph(int _V = 0) : V(_V){
        ptrE = _memE;
        for (int i = 0 ; i < V ; i++) node[i] = _memN;
    }
};
int main(){

}
