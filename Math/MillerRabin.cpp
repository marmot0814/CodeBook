#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL modMul(LL a, LL b, LL m){
    a %= m, b %= m;
    LL y = (LL)((double)a * b/ m + .5);
    LL r = (a * b - y * m) % m;
    return r < 0 ? r + m : r;
}
template <typename T>
inline T pow(T a, T b, T mod){
    T ans = 1;
    for (; b; a = modMul(a, a, mod), b >>= 1)
    if (b%2) ans = modMul(ans, a, mod);
    return ans;
}
int sprp[3] = {2, 7, 61};
int llsprp[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
template <typename T>
inline bool isPrime(T n, int *sprp, int num){
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    int t = 0;
    T u = n - 1;
    for (; u % 2 == 0; t++) u >>= 1;
    for (int i = 0 ; i < num ; i++){
        T a = sprp[i] % n;
        if (a == 0 || a == 1 || a == n-1) continue;
        T x = pow(a, u, n);
        if (x == 1 || x == n-1) continue;
        for (int j = 1 ; j < t ; j++){
            x = modMul(x, x, n);
            if (x == 1) return false;
            if (x == n - 1) break;
        }
        if (x == n - 1) continue;
        return false;
    }
    return true;
}

int main(){
	for (int i = 1 ; i < 100 ; i++)
		if (isPrime(i, llsprp, 7))
			cout << i << '\n';
}
