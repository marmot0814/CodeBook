#include <bits/stdc++.h>
using namespace std;
void ZAlg(char *s, int *Z){
	Z[0] = strlen(s);
	for (int L = 0, R = 0, i = 1; s[i] ; i++){
		if (i <= R && Z[i - L] <= R - i) Z[i] = Z[i - L];
		else{
			L = i; if (i > R) R = i;
			while (R < Z[0] && s[R - L] == s[R]) R++;
			Z[i] = (R--) - L;
		}
	}
}
int main(){
}
