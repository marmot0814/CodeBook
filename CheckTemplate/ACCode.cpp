#include<stdio.h>
#include<math.h>
const int MAX=50004*4;
int tree[MAX];
void add(int root)
{
	tree[root]=tree[2*root]+tree[2*root+1];
}
void buildtree(int root,int left,int right)
{
	if(left==right)
	{
		scanf("%d",&tree[root]);
		return;
	}
	int mid=(left+right)/2;
	buildtree(root*2,left,mid);
	buildtree(root*2+1,mid+1,right);
	add(root);
}
void update(int root,int left,int right,int position,int add_num)
{
	if(left==right)
	{
		tree[root]+=add_num;
		return;
	}
	int mid=(left+right)/2;
	if(position<=mid)
		update(root*2,left,mid,position,add_num);
	else
		update(root*2+1,mid+1,right,position,add_num);
	add(root);
}
int getsum(int root,int left,int right,int begin,int end)
{
	if(left==begin&&right==end)
		return tree[root];
	int mid=(left+right)/2,result=0;
	if(begin>mid)
		result+=getsum(root*2+1,mid+1,right,begin,end);
	else if(end<=mid)
		result+=getsum(root*2,left,mid,begin,end);
	else
	{
		result+=getsum(root*2+1,mid+1,right,mid+1,end);
		result+=getsum(root*2,left,mid,begin,mid);
	}
	return result;
}
int main()
{
	int t,n;
    scanf("%d", &t);
    for(int k=1;k<=t;k++)
    {
        scanf("%d", &n);
		buildtree(1, 1, n);
        char op[10];
        int t1, t2;
        printf("Case %d:\n", k);
        while(scanf("%s", op))
        {
           	if(op[0]=='E')
				break;
            scanf("%d %d",&t1,&t2);
            if(op[0]=='A')
               	update(1,1,n,t1,t2);
            else if(op[0]=='S')
                update(1,1,n,t1,-t2);
            else            
               	printf("%d\n",getsum(1,1,n,t1,t2));
     	}
    }
    return 0;
}
