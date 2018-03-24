#include <bits/stdc++.h>
using namespace std;
const int SIGMA = 26;
const int MAXNODE = 5e5 + 5;
struct AC{
    inline int idx(char c){
        return c - 'a';
    }
    struct Node{
        Node *fail, *next[SIGMA];
        bool vis;
        int dp;
        Node(){
            memset(next, 0, sizeof(next));
            dp = 0; fail = NULL;
            vis = false;
        }
    }*root, *ori, *ptr, _mem[MAXNODE];
    void init(){
        ptr = _mem;
        ori = new (ptr++) Node();
        root = new (ptr++) Node();
    }
    void buildTrie(char *s){
        Node *cur = root;
        for (int i = 0 ; s[i] ; i++){
            int c = idx(s[i]);
            if (cur->next[c] == NULL)
                cur->next[c] = new (ptr++) Node();
            cur = cur->next[c];
        }
        cur->dp++;
    }
    Node* trans(Node *cur, int c){
        while (cur->next[c] == NULL) cur = cur->fail;
        return cur->next[c];
    }
    void buildAC(){
        static queue<Node*> q;
        for (int i = 0 ; i < SIGMA ; i++)
            ori->next[i] = root;
        root->fail = ori;
        q.push(root);
        while (q.size()){
            Node *cur = q.front(); q.pop();
            for (int i = 0 ; i < SIGMA ; i++){
                if (cur->next[i] == NULL) continue;
                cur->next[i]->fail = trans(cur->fail, i);
                q.push(cur->next[i]);
            }
        }
    }
    int search(char *s){
        int ans = 0;
        Node *cur = root;
        for (int i = 0 ; s[i] ; i++){
            cur = trans(cur, idx(s[i]));
            Node *tmp = cur;
            while (tmp != root && !tmp->vis){
                ans += tmp->dp;
                tmp->vis = true;
                tmp = tmp->fail;
            }
        }
        return ans;
    }
};
AC sol;
const int MAXLEN = 1e6 + 5;
char buf[MAXLEN];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t; while (t--){
        sol.init();
        int n; cin >> n;
        for (int i = 0 ; i < n ; i++){
            cin >> buf;
            sol.buildTrie(buf);
        }
        sol.buildAC();
        cin >> buf;
        cout << sol.search(buf) << '\n';
    }
}
