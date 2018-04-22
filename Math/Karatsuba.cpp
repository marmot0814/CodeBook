#include <bits/stdc++.h>
using namespace std;
template <typename T>
void karatsuba(int n, T* A, T* B, T* R){ // n = (1<<k)
    memset(R, 0, sizeof(T) * 2 * n);
    if (n <= 16) {
        for (int i =0 ; i < n ; i++)
            for (int j = 0 ; j < n ; j++)
                R[i + j] += A[i] * B[j];
        return ;
    }
    int m = n >> 1; 
    karatsuba(m, A, B, R);
    karatsuba(m, A + m, B + m, R + n);
    T* a = new T[m], *b = new T[m], *r = new T[n];
    for (int i = 0 ; i < m ; i++) a[i] = A[i] + A[i + m], b[i] = B[i] + B[i + m];
    karatsuba(m, a, b, r);
    for (int i = 0 ; i < n ; i++) r[i] -= R[i], r[i] -= R[i + n];
    for (int i = 0 ; i < n ; i++) R[i + m] += r[i];
    delete [] a; delete [] b; delete [] r;
}
const int MAXV = (1 << 16) + 5;
typedef long long LL;
int main(){
    
}
