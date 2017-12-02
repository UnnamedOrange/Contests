#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int c[20202];
char a[20202][101];
int main()
{
	int n,m,i,ca,j,k,l;
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%s",a[i]+1);
	for(i=1;i<=m;i++)
	{
		scanf("%d",&ca);
		if(ca==1)
		{
			n++;
			scanf("%s",a[n]+1);
		}
		else
		{
			scanf("%d",&k);
			for(j=1;j<=k;j++)
				scanf("%d",&c[j]);
			for(l=1;l<=100;l++)
			{	
				for(j=2;j<=k;j++)
				{
					//printf("%c %c",a[c[j]][strlen(a[c[j]])-l+1],a[c[j-1]][strlen(a[c[j-1]])-l+1]);
					if(strlen(a[c[j]]+1)-l+1<=0||a[c[j]][strlen(a[c[j]]+1)-l+1]!=a[c[j-1]][strlen(a[c[j-1]]+1)-l+1])
						break;
				}
				if(j<=k)
					break;
			}
			printf("%d\n",l-1);
		}
	}
	return 0;
}
