#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 300005
#define MAXC 300005
int n,m;
int a[MAXN];
int colcnt[MAXC],colpos[MAXC];
int cla=2;
using namespace std;

void work1()
{
	for(int i=1;i<=m;i++)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			int l,r,c;
			int ans=0;
			scanf("%d%d%d",&l,&r,&c);
			for(int j=l;j<=r;j++)
			{
				if(a[j]==c) ans++;
			}
			printf("%d\n",ans);
		}
		else if(opt==2)
		{
			int x;
			scanf("%d",&x);
			swap(a[x],a[x+1]);
		}
	}
}

void work2()
{
	for(int i=1;i<=m;i++)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			int l,r,c;
			int ans=0;
			scanf("%d%d%d",&l,&r,&c);
			if(r-l<=20)
			{
				for(int j=l;j<=r;j++) if(a[j]==c) ans++;
			}
			else
			{
				ans+=colcnt[c];
				for(int j=1;j<=l-1;j++) if(a[j]==c) ans--;
				for(int j=r+1;j<=n;j++) if(a[j]==c) ans--;
			}
			printf("%d\n",ans);
		}
		else if(opt==2)
		{
			int x;
			scanf("%d",&x);
			swap(a[x],a[x+1]);
		}
	}
}

void work3()
{
	for(int i=1;i<=m;i++)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			int l,r,c;
			int ans=0;
			scanf("%d%d%d",&l,&r,&c);
			if(colpos[c]<=r && colpos[c]>=l) printf("1\n");
			else printf("0\n");
		}
		else if(opt==2)
		{
			int x;
			scanf("%d",&x);
			swap(colpos[a[x]],colpos[a[x+1]]);
			swap(a[x],a[x+1]);
		}
	}
}

int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		colcnt[a[i]]++;
		colpos[a[i]]=i;
		if(colcnt[a[i]]>1) cla=1;
	}
	if(n<=1000) work1();
	else if(cla==1) work2();
	else if(cla==2) work3();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
