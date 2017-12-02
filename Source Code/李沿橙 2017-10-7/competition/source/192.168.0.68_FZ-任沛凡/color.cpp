#include<cmath>
#include<cstdio>
#include<iostream>
#define maxn 300010
#define maxm 175
using namespace std;
int l[maxm],r[maxm],mid[maxm];
int a[maxn],bel[maxn],cnt[maxm][maxn];
int n,m,k,blo,sum;
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int op,x,y,z;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	k=170;
	blo=ceil((double)n/k);
	for(int i=1;i<=n;i++)
	bel[i]=(i-1)/blo+1;
	for(int i=1;i<=k;i++)
	l[i]=(i-1)*blo+1,r[i]=i*blo;
	r[k]=n;
	for(int i=1;i<=k;i++)
	mid[i]=(l[i]+r[i])>>1;
	for(int i=1;i<=k;i++)
	for(int j=l[i];j<=r[i];j++)
	cnt[i][a[j]]++;
	while(m--)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&x,&y,&z);
			sum=0;
			for(int i=bel[x]+1;i<=bel[y]-1;i++)
			sum+=cnt[i][z];
			if(x>=mid[bel[x]])
			{
				for(int i=x;i<=r[bel[x]];i++)
				if(a[i]==z)
				sum++;
			}
			else
			{
				sum+=cnt[bel[x]][z];
				for(int i=l[bel[x]];i<x;i++)
				if(a[i]==z)
				sum--;
			}
			if(y<=mid[bel[y]])
			{
				for(int i=l[bel[y]];i<=y;i++)
				if(a[i]==z)
				sum++;
			}
			else 
			{
				sum+=cnt[bel[y]][z];
				for(int i=y+1;i<=r[bel[y]];i++)
				if(a[i]==z)
				sum--;
			}
			printf("%d\n",sum);
		}
		else
		{
			scanf("%d",&x);
			if(bel[x]!=bel[x+1])
			{
				cnt[bel[x]][a[x]]--;
				cnt[bel[x]][a[x+1]]++;
				cnt[bel[x+1]][a[x]]++;
				cnt[bel[x+1]][a[x+1]]--;
			}
			swap(a[x],a[x+1]);
		}
	}
	return 0;
}
	
