#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define T 1000010
#define S 10010
#define N 150010
#define SIG 26
#define LOG 15
#define InS() {scanf("%s",s+1);int x=strlen(s+1);\
			for(int i=1;i<=x/2;i++) swap(s[i],s[x-i+1]);\
			pos[++scnt]=insert_trie(rt,s,x);}
#define toi(x) (x-'a')
using namespace std;
int t[T][SIG],up[T][LOG],tcnt,scnt,dep[T];
inline int insert_trie(int now,char *s,int n)
{
	for(int i=1;i<=n;i++)
	{
		int c=toi(s[i]),&ch=t[now][c];
		if(!ch)
		{
			up[ch=++tcnt][0]=now;
			for(int j=1;j<LOG;j++)
				up[ch][j]=up[up[ch][j-1]][j-1];
		}
		dep[ch]=dep[now]+1;
		now=t[now][c];
	}
	return now;
}
inline int getLCA(int u,int v)
{
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=LOG-1;i>=0;i--)
		if(dep[up[u][i]]>=dep[v])
			u=up[u][i];
	if(u==v) return v;
	for(int i=LOG-1;i>=0;i--)
		if(up[u][i]^up[v][i])
			u=up[u][i],v=up[v][i];
	return up[v][0];
}
char s[S],pos[N];
#define gc getchar
inline int inn()
{
	char ch;while((ch=gc())>'9'||ch<'0');
	int x=ch^'0';
	while((ch=gc())>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^'0');
	return x;
}
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	int n,m,rt=++tcnt;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) InS();
	while(m--)
	{
		int opt;scanf("%d",&opt);
		if(opt==1) InS()
		else{
			int x;scanf("%d",&x);x-=2;
			int c=getLCA(pos[inn()],pos[inn()]);
			while(x--) c=getLCA(c,pos[inn()]);
			printf("%d\n",dep[c]);
		}
	}
	return 0;
}
/*
5 5
zzj
pri
prime
ime
owaski
2 3 1 3 5
2 2 2 3
1 actri
2 2 3 4
2 3 2 6 5
*/
