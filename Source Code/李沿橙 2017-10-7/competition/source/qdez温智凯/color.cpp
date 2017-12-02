#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<iostream>
using namespace std;
const int MAXN=300010;
int a[MAXN],b[MAXN];
int main()
{
	int k,l,m,n,c,x,y,z,cnt;
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d%d",&n,&m);
	
	if (n>1000)
	{
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&b[i]);
			a[b[i]]=i;
		}
		while(m--)
		{
			scanf("%d",&c);
			if (c==1) 
			{
				scanf("%d%d%d",&x,&y,&z);
				if (a[z]>=x && a[z]<=y)
				{
					printf("1\n");
				}
				else
				{
					printf("0\n");
				}
			}
			else
			{
				scanf("%d",&x);
				swap(a[b[x]],a[b[x+1]]);
			}
		} 
		return 0;
	}
	
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	while(m--)
	{
		scanf("%d",&c);
		if (c==1)
		{
			scanf("%d%d%d",&x,&y,&z);
			cnt=0;
			for (int i=x;i<=y;i++) if (a[i]==z) cnt++;
			printf("%d\n",cnt);
		}
		else
		{
			scanf("%d",&x);
			swap(a[x],a[x+1]);
		}
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}

