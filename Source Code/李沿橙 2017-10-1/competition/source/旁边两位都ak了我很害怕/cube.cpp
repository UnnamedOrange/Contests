#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
int fa[30001],dep[30001],go[30001];
char ch[10];
int findfa(int x){return fa[x]<0?x:fa[x]=findfa(fa[x]);}
void mer(int x,int y)
{	int fax=findfa(x),fay=findfa(y);
	if(fax!=fay)
	{	go[fax]=fay,dep[fax]=-fa[fay];
		fa[fay]=fa[fay]+fa[fax]; fa[fax]=fay;
	}
}
int solve(int x)
{	int ans=0,k=x;
	while(go[x]!=x)
	{	ans+=dep[x];
		x=go[x];
	}
	dep[k]=ans;go[k]=x;
	while(go[x]!=x)
	{	dep[x]=ans;
		go[x]=go[k];
	}
	return ans;
}
int main()
{   freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int p,n=30000,x,y; cin>>p;
	for(rint i=1;i<=n;i++) fa[i]=-1,go[i]=i,dep[i]=0;
	for(rint i=1;i<=p;i++)
	{	scanf("%s",ch+1);
		if(ch[1]=='M') scanf("%d%d",&x,&y),mer(x,y);
		if(ch[1]=='C') scanf("%d",&x),printf("%d\n",solve(x));
	}
 	return 0;
}


