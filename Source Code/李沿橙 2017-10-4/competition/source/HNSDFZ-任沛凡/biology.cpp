#include<cstdio>
#include<cstring>
#include<iostream>
#define maxn 100010
#define maxm 1000010
using namespace std;
int a[maxm][26];
int bin[50],f[maxn];
int fa[maxm][21],d[maxm];
char s[maxn];
int n,m,cnt,tot;
void insert(int k)
{
	int x,len,y;
	x=0;
	len=strlen(s+1);
	for(int i=len;i;i--)
	{
		y=s[i]-'a';
		if(!a[x][y])
		{
			a[x][y]=++cnt;
			fa[cnt][0]=x;
			d[cnt]=d[x]+1;
			for(int j=1;bin[j]<=d[cnt];j++)
			fa[cnt][j]=fa[fa[cnt][j-1]][j-1];
		}
		x=a[x][y];
	}
	f[k]=x;
}
int lca(int x,int y)
{
	if(d[x]<d[y])
	swap(x,y);
	int t=d[x]-d[y];
	for(int i=0;bin[i]<=t;i++)
	if(bin[i]&t)
	x=fa[x][i];
	for(int i=20;i>=0;i--)
	if(fa[x][i]!=fa[y][i])
	x=fa[x][i],y=fa[y][i];
	if(x==y)
	return x;
	return fa[x][0];
}
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	int x,y,k,op;
	bin[0]=1;
	for(int i=1;i<=20;i++)
	bin[i]=bin[i-1]<<1;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		insert(i);
	}
	tot=n;
	while(m--)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%s",s+1);
			++tot;
			insert(tot);
		}
		else
		{
			scanf("%d",&k);
			scanf("%d",&x);
			x=f[x];
			for(int i=1;i<k;i++)
			{
				scanf("%d",&y);
				x=lca(x,f[y]);
			}
			printf("%d\n",d[x]);
		}
	}
	return 0;
}
			
