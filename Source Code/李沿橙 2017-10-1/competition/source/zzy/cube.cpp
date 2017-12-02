#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 30005

int p;
int fa[N],num[N],gs[N],ans[N];
char op[5];

int getf(int x)
{
	if (x==fa[x]) return x;
	num[x]+=num[fa[x]];
	fa[x]=getf(fa[x]);
	return fa[x];
}
void merge(int x,int y)
{
	int t1=getf(x),t2=getf(y);
	fa[t1]=t2;num[t1]+=gs[t2];
	gs[t2]+=gs[t1];
}
void brute()
{
	while (p--)
	{
		int x,y;scanf("%s",op);
		if (op[0]=='C')
		{
			scanf("%d",&x);
			printf("%d\n",ans[x]);
		}
		else 
		{
			scanf("%d%d",&x,&y);
			int pl=gs[y],sum=gs[x]+gs[y],ls=fa[x];
			for (int i=1;i<=10;i++)
			{
				if (fa[i]==fa[y])
				gs[i]=sum;
			}
			for (int i=1;i<=10;i++)
			{
				if (fa[i]==ls)
				ans[i]+=pl,gs[i]=sum,fa[i]=fa[y];
			}
		}
	}
}

int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	
	scanf("%d",&p);
	for (int i=1;i<=30001;i++) gs[i]=1,fa[i]=i;
	if (p<=3000) {brute();return 0;}
	while (p--)
	{
		int x,y;scanf("%s",op);
		if (op[0]=='C')
		{
			scanf("%d",&x);
			fa[x]=getf(x);
			printf("%d\n",num[x]);
		}
		else 
		{
			scanf("%d%d",&x,&y);
			merge(x,y);
		}
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
