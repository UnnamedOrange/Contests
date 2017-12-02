#include<cstdio>
#define maxn 30010
using namespace std;
int n=30000,m;
int a[maxn],b[maxn],fa[maxn];
int find(int x)
{
	if(x==fa[x])
	return x;
	int tmp=find(fa[x]);
	a[x]+=a[fa[x]];
	return fa[x]=tmp;
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int x,y,p,q;
	char s[10];
	scanf("%d",&m);
	for(int i=1;i<=n;i++)
	fa[i]=i,b[i]=1;
	while(m--)
	{
		scanf("%s",s);
		if(s[0]=='M')
		{
			scanf("%d%d",&x,&y);
			p=find(x);
			q=find(y);
			fa[p]=q;
			a[p]=b[q];
			b[q]+=b[p];
		}
		else
		{	
			scanf("%d",&x);
			find(x);
			printf("%d\n",a[x]);
		}
	}
	return 0;
}
