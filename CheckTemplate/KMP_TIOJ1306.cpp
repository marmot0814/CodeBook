#include <bits/stdc++.h>
using namespace std;
const int MAXLEN = 1e4 + 5;
int F[MAXLEN];
void build(char *s){
    F[0] = -1;
    for (int i = 1, pos = -1; s[i] ; i++){
        while (~pos && s[i] != s[pos + 1]) pos = F[pos];
        if (s[i] == s[pos + 1]) pos++;
        F[i] = pos;
    }
}
int match(char *_find, char *content){
    int ans = 0;
    int findLen = strlen(_find);
    for (int i = 0, pos = -1; content[i] ; i++){
        while (~pos && content[i] != _find[pos + 1]) pos = F[pos];
        if (content[i] == _find[pos + 1]) pos++;
        if (pos + 1 == findLen) ans++, pos = F[pos];
    }
    return ans;
}
int main(){ ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while (t--) {
        char s[MAXLEN]; cin >> s;
        int q; cin >> q;
        while (q--) {
            char a[MAXLEN]; cin >> a;
            build(a);
            cout << match(a, s) << '\n';
        }
    }
}
