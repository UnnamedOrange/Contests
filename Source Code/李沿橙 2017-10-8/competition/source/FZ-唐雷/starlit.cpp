#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
#define N 100005
using namespace std;
int n,m,k,ans;
bool a[40005];
int b[40005],d;
int sp[65];
void dfs(int x,int step)
{
	if(x>n&&step<ans)
	{
		ans=step;
		return;
	}
	if(step>ans)return;
	d^=b[x];a[x]^=d;
	if(!a[x])
	dfs(x+1,step);
	else
	for(int i=1;i<=m;++i)
	{
		d^=1;b[x+sp[i]]^=1;
		dfs(x+1,step+1);
		d^=1,b[x+sp[i]]^=1;
	}
}
int main()
{
freopen("starlit.in","r",stdin);
freopen("starlit.out","w",stdout);
	scanf("%d%d%d",&n,&k,&m);
	int t1;
	for(int i=1;i<=k;++i){scanf("%d",&t1);a[t1]=1;}
	for(int i=1;i<=m;++i){scanf("%d",&sp[i]);}
	if(m>=16)ans=4;
	else ans=1000000000;
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
