#include <bits/stdc++.h>
using namespace std;
struct Matrix {
    vector<vector<int> > m;
    int r, c;
    Matrix(int _r, int _c) : r(_r), c(_c) {
        m.resize(r, vector<int>(c));
    }
    vector<int>& operator[](int i) { return m[i]; }
    Matrix operator + (const Matrix &M) const {
        Matrix res(r, c);
        for (int i = 0 ; i < r ; i++)
            for (int j = 0 ; j < c ; j++)
                res[i][j] = m[i][j] + M.m[i][j];
        return res;
    }
    Matrix operator - (const Matrix &M) const {
        Matrix res(r, c);
        for (int i = 0 ; i < r ; i++)
            for (int j = 0 ; j < c ; j++)
                res[i][j] = m[i][j] - M.m[i][j];
        return res;
    }
    Matrix operator * (const Matrix &M) const {
        Matrix res(r, M.c);
        for (int i = 0 ; i < r ; i++)
            for (int j = 0 ; j < M.c ; j++)
                for (int k = 0 ; k < c ; k++)
                    res[i][j] += m[i][k] * M.m[k][j];
        return res;
    }
    Matrix operator ^ (int n) const {
        if (n == 1) return *this;
        Matrix k = *this ^ (n / 2);
        if (n % 2) return k * k * *this;
        else return k * k;
    }
    Matrix operator % (int n) const {
        Matrix res(r, c);
        for (int i = 0 ; i < r ; i++)
            for (int j = 0 ; j < c ; j++)
                res[i][j] = m[i][j] % n;
        return res;
    }
    friend ostream& operator << (ostream& out, const Matrix &M) {
        for (int i = 0 ; i < M.r ; i++)
            for (int j = 0 ; j < M.c ; j++)
                out << M.m[i][j] << (j == M.c - 1 ? '\n' : ' ');
        return out;
    }
    friend istream& operator >> (istream& in, Matrix &M) {
        for (int i = 0 ; i < M.r ; i++)
            for (int j = 0 ; j < M.c ; j++)
                in >> M[i][j];
        return in;
    }
};
int main() {
    Matrix m(4, 4); cin >> m;
    cout << m << '\n';
    cout << (m ^ 5) << '\n';
}

