#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL modPow(LL a, LL x, LL m){
    if (x == 0) return 1;
    LL k = modPow(a, x / 2, m);
    if (x & 1) return k * k % m * a % m;
    else return k * k % m;
}
const int MAXN = 1e9 + 5;
const int sqrtN = sqrt(MAXN) + 5;
vector<bool> isPrime(sqrtN, true);
vector<int> Prime;
void linearPrime(){
    isPrime[0] = isPrime[1] = false;
    for (int i = 2 ; i < sqrtN ; i++){
        if (isPrime[i]){
            Prime.push_back(i);
            for (int j = 2 * i ; j < sqrtN ; j += i)
                isPrime[j] = false;
        }
    }
}
bool isPrimativeRoot(int a, int x){
    vector<int> primeFactor;
    int target = x - 1;
    for (auto p : Prime){
        if (target < p) break;
        bool _find = false;
        while (target % p == 0) target /= p, _find = true;
        if (_find) primeFactor.push_back(p);
    }
    for (auto p : primeFactor)
        if (modPow(a, (x - 1) / p, x) == 1) return false;
    return true;
}
int main(){ ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n; linearPrime();
    int ans = 0; while (1){
        ans++;
        if (!isPrimativeRoot(ans, n)) continue;
        cout << ans << '\n'; break;
    }
}
