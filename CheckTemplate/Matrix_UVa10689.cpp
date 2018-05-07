#include <bits/stdc++.h>
using namespace std;
int MOD;
struct Matrix {
    vector<vector<int> > m;
    int r, c;
    Matrix(int _r, int _c) : r(_r), c(_c) {
        m.resize(r, vector<int>(c, 0));
    }
    vector<int>& operator[](int i) { return m[i]; }
    Matrix operator * (const Matrix &M) const {
        Matrix res(r, M.c);
        for (int i = 0 ; i < r ; i++)
            for (int j = 0 ; j < M.c ; j++)
                for (int k = 0 ; k < c ; k++)
                    res[i][j] += m[i][k] * M.m[k][j];
        return res;
    }
    Matrix operator ^ (int n) const {
        if (n == 1) return *this % MOD;
        Matrix k = *this ^ (n / 2);
        if (n % 2) return *this * k % MOD * k % MOD;
        else return k * k % MOD;
    }
    Matrix operator % (int n) const {
        Matrix res(r, c);
        for (int i = 0 ; i < r ; i++)
            for (int j = 0 ; j < c ; j++)
                res[i][j] = m[i][j] % n;
        return res;
    }
};
int main() { ios_base::sync_with_stdio(false); cin.tie(0);
    Matrix A(2, 2);
    A[0][0] = 1; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 0;
    int t; cin >> t; while (t--) {
        int a, b, n, m; cin >> a >> b >> n >> m;
        MOD = 1; for (int i = 0 ; i < m ; i++) MOD *= 10;
        if (n == 0) { cout << a % MOD << '\n'; continue; }
        if (n == 1) { cout << b % MOD << '\n'; continue; }
        Matrix base(2, 1);
        base[0][0] = b; base[1][0] = a;
        Matrix res = A ^ (n - 1), ans = res * base; 
        cout << ans[0][0] % MOD << '\n';
    }
}

