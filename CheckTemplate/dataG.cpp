#include<cstdio>
#include<ctime>
#include<cstring>
#include<cstdlib>
int n = 50;    //模式串个数
int Len = 50;     //每个模式串限定长度
int MaxLen = 1000000;  //主串限定长度
int Case = 10;    //测试数据组数
int main()
{
	printf("%d\n",Case);
	while(Case--)
	{
		srand(time(NULL) * rand() % 19980518 % rand() * 10001 % 2347);
		printf("%d\n",n);
		int i,j;
		for(i = 1 ; i <= n ; ++i)
		{
			int len = rand() % (Len - 3) + 3;
			for(j = 1 ; j <= len ; ++j)
			{
				printf("%c",rand()%26+'a');
			}
			puts("");
		}
		int Max = rand() % (MaxLen - 3) + 3;
		for(j = 1 ; j <= Max ; ++j)
		{
			printf("%c",rand()%26+'a');
		}
		puts("");
	}
}
