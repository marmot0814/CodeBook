#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL extgcd(LL a, LL b, LL &x, LL &y){
    LL d = a;
    if (b != 0){
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }else x = 1, y = 0;
    return d;
}
LL modInv(LL a, LL m){
    LL x, y, d = extgcd(a, m, x, y);
    return d == 1 ? (m + x % m) % m : -1;
}

int main(){

}
