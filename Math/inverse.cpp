#include <bits/stdc++.h>
using namespace std;
int extgcd(int a, int b, int &x, int &y){
    int d = a;
    if (b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }else x = 1, y = 0;
    return d;
}
int modInv(int a, int m){
    int x, y;
    extgcd(a, m, x, y);
    return m + (x % m) % m;
}
int mod = 616069;
int main(){
    for (int i = 0 ; i < 100 ; i++){
        int r = modInv(i, mod);
        cout << r << ' ' << (r * i) % mod << '\n';
    }
}
