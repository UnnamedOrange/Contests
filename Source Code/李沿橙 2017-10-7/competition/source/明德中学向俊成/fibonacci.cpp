#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	freopen("fibonacci.in","r",stdin);freopen("fibonacci.out","w",stdout);
	int i,j,k,m,n,x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		if(x==y)printf("%d\n",x);
		else
		{
			printf("1\n");
		}
	}
	return 0;
}
