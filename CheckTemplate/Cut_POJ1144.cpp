// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
const int MAXN = 1e2 + 5;
struct Graph{
    struct Node : vector<Node*> {
        int low, dfn;
        bool is_cut;
        Node *pa;
        Node () {
            clear(), low = dfn = -1;
            is_cut = false; pa = NULL;
        }
    }_memN[MAXN], *node[MAXN];
    int V;
    Graph(int _V) : V(_V) {
        for (int i = 0 ; i < V ; i++)
            node[i] = _memN + i;
    }
    void addEdge(int u, int v){
        node[u]->push_back(node[v]);
        node[v]->push_back(node[u]);
    }

    int stamp;
    int findCutAndBridge(){
        stamp = 0; int root_son = 0;
        int ans = 0;
        Tarjan(node[0], NULL);
        for (int i = 1 ; i < V ; i++){
            Node *pa = node[i]->pa;
            if (pa == node[0]) root_son++;
            else {
                if (node[i]->low >= pa->dfn)
                    pa->is_cut = true;
            }
        }
        if (root_son > 1) node[0]->is_cut = true;
        for (int i = 0 ; i < V ; i++)
            if (node[i]->is_cut)
                ans++;
        return ans;
        for (int i = 0 ; i < V ; i++){
            Node *pa = node[i]->pa;
            if (pa && node[i]->low > pa->dfn);
                /* pa and node[i] is a bridge*/
        }
    }
    void Tarjan(Node *u, Node *pa){
        u->pa = pa;
        u->dfn = u->low = stamp++;
        // for (auto to : *u){
        for (int i = 0 ; i < u->size() ; i++) {
            Node *to = u->at(i);
            if (!~to->dfn) {
                Tarjan(to, u);
                u->low = min(u->low, to->low);
            }else if (pa != to)
                u->low = min(u->low, to->dfn);
        }
    }
};
const int MAXLEN = 1e4 + 5;
int main() { 
    int n; while (cin >> n && n) {
        Graph *G = new Graph(n);
        char input[MAXLEN]; fgets(input, MAXLEN, stdin);
        while (fgets(input, MAXLEN, stdin)){
            if (input[0] == '0') break;
            strtok(input, "\n");
            int u = atoi(strtok(input, " "));
            for (char *ptr = strtok(NULL, " ") ; ptr ; ptr = strtok(NULL, " ")){
                int v = atoi(ptr);
                G->addEdge(u - 1, v - 1);
            }
        }
        cout << G->findCutAndBridge() << '\n';
    }
}
