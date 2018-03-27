#include <bits/stdc++.h>
using namespace std;
const int MAXP = 100;
int main(){
	int PHI[MAXP + 2];
	for (int i = 1 ; i <= MAXP ; i++) PHI[i] = i;
	for (int i = 2 ; i <= MAXP ; i += 2) PHI[i] /= 2;
	for (int i = 3 ; i <= MAXP ; i += 2)
		if (PHI[i] == i)
			for (int j = i ; j <= MAXP ; j += i)
				PHI[j] = PHI[j] / i * (i - 1);
	for (int i = 1 ; i <= MAXP ; i++)
		cout << PHI[i] << (i == MAXP ? '\n' : ' ');
}
