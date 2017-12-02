#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
#define MAXN 100005
#define TOTL 100005
int n,m,t;
int len[MAXN];
int a[15];
using namespace std;
vector <char> s[MAXN];

struct POINT
{
	int du;
	int son[27];
	int tim[27];
}p[TOTL];

int cnt=0;
void ADD(int x)
{
	int fa=0;
	for(int i=len[x]-1;i>=0;i--)
	{
		if(p[fa].son[s[x][i]-'a']==0)
		{
			cnt++;
			p[fa].son[s[x][i]-'a']=cnt;
			p[fa].du++;
		}
		p[fa].tim[s[x][i]-'a']++;
		fa=p[fa].son[s[x][i]-'a'];
	}
}

void get_ans()
{
	int x=0,tmpans=0;
	while(p[x].du==1)
	{
		int fff=0;
		for(int i=0;i<=26;i++)
		{
			if(p[x].son[i]!=0 && p[x].tim[i]==t)
			{
				x=p[x].son[i];
				tmpans++;
				break;
			}
			if(i==26) fff=1;
		}
		if(fff==1) break;
	}
	printf("%d\n",tmpans);
}

int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		char tmpch=' ';
		while(tmpch<'a' || tmpch>'z') tmpch=getchar();
		while(tmpch>='a' && tmpch<='z')
		{
			len[i]++;
			s[i].push_back(tmpch);
			tmpch=getchar();
		}
	}
	for(int i=1;i<=m;i++)
	{
		int opt;
		scanf("%d",&opt);
		if(opt==1)
		{
			n++;
			char tmpch=' ';
			while(tmpch<'a' || tmpch>'z') tmpch=getchar();
			while(tmpch>='a' && tmpch<='z')
			{
				len[n]++;
				s[n].push_back(tmpch);
				tmpch=getchar();
			}
		}
		else if(opt==2)
		{
			scanf("%d",&t);
			for(int j=0;j<=cnt;j++)
			{
				p[j].du=0;
				for(int k=0;k<=26;k++)
				{
					p[j].tim[k]=0;
					p[j].son[k]=0;
				}
			}
			cnt=0;
			for(int j=1;j<=t;j++)
			{
				scanf("%d",&a[j]);
				ADD(a[j]);
			}
			get_ans();
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
