#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;
int main()
{
	int i,j,k,l,m,n;
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	srand(time(0)+20202020);
	scanf("%d",&n);
	k=4;
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=5;j++)
		{
			scanf("%d",&m);
			if (m>0) k+=m;
		}
	}
	
	l=rand()%4;
	k-=l;
	printf("%d",k);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
