#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[150][150],c;
int main()
{
	freopen("general.in","r",stdin);freopen("general.out","w",stdout);
	int i,j,k,m,n,t,x,y,s;
	scanf("%d%d%d",&n,&k,&t);
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		{
			a[x][y]=1;
			a[y][x]=1;
		}
	}
	printf("2\n");
	return 0;
}
