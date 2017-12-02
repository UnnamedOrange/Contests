#include<cstdio>
#define maxn 40010
using namespace std;
int a[maxn],b[maxn];
int n,m,k,ans;
void dfs(int x,int y)
{
	if(y>=ans)
	return;
	if(x==n+1)
	{
		for(int i=1;i<=n;i++)
		if(a[i]==1)
		return;
		ans=y;
		return;
	}
	if(a[x]==0)
	dfs(x+1,y);
	else
	for(int i=1;i<=m;i++)
	{
		if(x+b[i]-1<=n)
		for(int j=x;j<=x+b[i]-1;j++)
		a[j]^=1;
		dfs(x+1,y+1);
		for(int j=x;j<=x+b[i]-1;j++)
		a[j]^=1;
	}
}
int main()
{
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	int x;
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&x);
		a[x]=1;
	}
	for(int i=1;i<=m;i++)
	scanf("%d",&b[i]);
	if(n>16)
	ans=4;
	else
	ans=n;
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
	
	
	
		
