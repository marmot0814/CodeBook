#include <bits/stdc++.h>
using namespace std;
string minStringRotate(string s){
    int n = s.length();
    s += s;
    int i=0, j=1;
    while (i<n && j<n){
        int k = 0;
        while (k < n && s[i+k] == s[j+k]) k++;
        if (s[i+k] <= s[j+k]) j += k+1;
        else i += k+1;
        if (i == j) j++;
    }
    int ans = i < n ? i : j;
    return s.substr(ans, n);
}
int main() {
    string s; while (cin >> s) {
        cout << minStringRotate(s) << '\n';
    }
}
