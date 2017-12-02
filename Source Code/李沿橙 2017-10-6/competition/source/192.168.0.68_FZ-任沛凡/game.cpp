#include<cstdio>
#include<cstring>
#include<iostream>
#define maxn 100010
#define ll long long
#define mod 1000000007
using namespace std;
int a[maxn];
int f[2][maxn];
int n,m,now,pre;
int inc(int x,int y)
{
	if(x+y>=mod)
	return x+y-mod;
	return x+y;
}
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	int op,x,l,r,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]),a[i]=inc(a[i],mod);
	while(m--)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d",&l,&r,&v);
			v=inc(v,mod);
			for(int i=l;i<=r;i++)
			a[i]=inc(a[i],v);
		}
		else if(op==2)
		{
			scanf("%d%d",&l,&r);
			for(int i=l;i<=r;i++)
			a[i]=mod-a[i];
		}
		else 
		{
			scanf("%d%d%d",&l,&r,&v);
			memset(f,0,sizeof(f));
			f[0][0]=1;
			now=0;
			pre=1;
			for(int i=1;i<=r-l+1;i++)
			{
				swap(now,pre);
				f[now][0]=1;
				for(int j=1;j<=v&&j<=i;j++)
				{
					f[now][j]=f[pre][j];
					f[now][j]=inc(f[now][j],(ll)f[pre][j-1]*a[l+i-1]%mod);
				}
				
			}
			x=(r-l+1)&1;
			printf("%d\n",f[x][v]);
		}
	}
	return 0;
}
			
				
				
				
				
				
				
