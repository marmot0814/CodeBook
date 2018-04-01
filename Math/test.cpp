#include <iostream>
#include <stdio.h>

using namespace std;

int d;
void ext_gcd(int a,int b,int &x,int &y)
{
    if(!b){d=a;x=1;y=0;return ;}//ax-by==a has solution (1,0)
    ext_gcd(b,a%b,x,y);//after this we have x=x0,y=y0 and bx0-(a%b)y0==d
    int x0=x,y0=y;
    /*
    a=bq+r
    bx0-ry0==d
    To solve ax-by==d:
    we have
      ax-by
    == (bq+r)x-by
    == bqx-by + rx
    == b(qx-y) + rx
    == bx0     - ry0
        / qx-y==x0
    => {
        \ x=-y0
    */
    x=-y0;
    y=-(a/b)*y0-x0;
}

int main()
{
    int a,b,x,y;
    while(scanf("%d%d",&a,&b)==2)
    {
        ext_gcd(a,b,x,y);
        printf("%d %d %d\n",d,x,y);
    }
    return 0;
}
