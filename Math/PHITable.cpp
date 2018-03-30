#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
long long int PHI[MAXN + 1];
void PHITable(){
    for (int i = 1 ; i <= MAXN ; i++) PHI[i] = i;
    for (int i = 1 ; i <= MAXN ; i++) 
        for (int j = i * 2 ; j <= MAXN ; j += i)
            PHI[j] -= PHI[i];
}
