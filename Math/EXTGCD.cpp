#include <bits/stdc++.h>
using namespace std;
void gcd(int a, int b, int &d, int &x, int &y){
	if (!b) { d = a, x = 1, y = 0; return ;}
	gcd(b, a%b, d, y, x);
	y -= x * (a / b);
}
int inverse(int a, int m){
	int d, x, y;
	gcd(a, m, d, x, y);
	return d == 1 ? (x + m) % m : -1;
}
const int mod = 1000000007;
int main(){
    long long a = 6;
    long long b = inverse(a, mod);
    cout << (b*24)%mod << '\n';
}
