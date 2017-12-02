#include<iostream>
#include<cstdio>
using namespace std;
int hi[30007]={1};
int hs[30007]={0};
int pl[30007]={0};
int a[30007][507]={0};
int anw[30007];
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int q,p,x,y,i,j,z,to=1;
	char zx;
	scanf("%d",&p);
	for(p;p>=1;p--)
	{
		scanf("\n%c",&zx);
		if(zx=='M')
		{
			scanf(" %d %d",&x,&y);
			if(pl[x]==0)
			{
			pl[x]=x;
			a[x][1]=x;
			hi[x]=1;
			}
			if(pl[y]==0)
			{
			pl[y]=y;
			a[y][1]=y;
			hi[y]=1;
			}
			j=pl[x];
			for(i=1;i<=hi[pl[x]];i++)
			{
			hs[a[pl[x]][i]]+=hi[pl[y]];
			a[pl[y]][hs[a[pl[x]][i]]+1]=a[pl[x]][i];
			pl[a[pl[x]][i]]=pl[y];
			}
			hi[pl[y]]+=hi[pl[x]];
			hi[j]=0;			
		}
		if(zx=='C')
		{
			scanf(" %d",&x);
			if(pl[x]==0)
			anw[to]=0;
			else anw[to]=hs[x];
			to++;
		}
	}
	for(q=1;q<to;q++)
	printf("%d\n",anw[q]);
	return 0;
}
