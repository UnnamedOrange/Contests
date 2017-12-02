#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#define L 1000005
#define N 50005
using namespace std;
vector<int>ques[100005];
struct node
{
	int son[26];	
}d[L];
int pla[N],siz=1,pos,cot;
char s[10005];
int n,m;
void insert(char s[],int len)
{
	int nw=1;
	for(int i=len;i>=0;--i)
	{
		int v=s[i]-'a';
		if(!d[nw].son[v])
		siz++,d[nw].son[v]=siz;
		nw=d[nw].son[v];
	}
	pla[++pos]=nw;
}
int deep[L],fa[L][30];
void dfs(int x,int f)
{
	deep[x]=deep[f]+1;
	fa[x][0]=f;
	for(int i=0;i<26;++i)
	{
		if(d[x].son[i])dfs(d[x].son[i],x);
	}
}
int lca(int x,int y)
{
	if(deep[x]<deep[y])swap(x,y);
	for(int i=21;i>=0;--i)
	{
		if(deep[fa[x][i]]>=deep[y])
		x=fa[x][i];
	}
	if(x==y)return x;
	for(int i=21;i>0;--i)
	{
		if(fa[x][i]!=fa[y][i])
		{
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s);
		insert(s,strlen(s)-1);
	}
	int typ,t1,t2;
	for(int i=1;i<=m;++i)
	{
		scanf("%d",&typ);
		if(typ==1)
		{
		scanf("%s",s);
		insert(s,strlen(s)-1);
		}
		else
		{
			scanf("%d",&t1);
			cot++;
			for(int i=1;i<=t1;++i)
			{
				scanf("%d",&t2);
				ques[cot].push_back(t2);
			}
		}
	}
	dfs(1,0);
	for(int i=1;i<22;++i)
	for(int j=1;j<=siz;++j)
	fa[j][i]=fa[fa[j][i-1]][i-1];
	for(int i=1;i<=cot;++i)
	{
		int x=pla[ques[i][0]],len=ques[i].size();
		for(int j=1;j<len;++j)
		{
			x=lca(x,pla[ques[i][j]]);
		}
		printf("%d\n",deep[x]-1);
	}
	return 0;
}
