#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

int read()
{
	int ret=0;
	char c=getchar();
	
	while (c<'0' || c>'9') c=getchar();
	
	while (c>='0' && c<='9') {
		ret=ret*10+c-'0'; c=getchar(); }
	
	return ret;
}

const int MAXLOG=20,MAXT=1000000;

const int MAXN=100000,MAXL=10000;

int LOG[MAXL+10];

int n,m,len,cnt;

int pos[MAXN+10];

char last[MAXN+10];

struct Trie
{
	int s[26];
	int f[MAXLOG+10];
	int dep;
}tr[MAXT+10];

char str[MAXL+10];

void insert(int x)
{
	last[x]=str[len-1];
	
	int now=1;
	for (int i=len-1;i>=0;i--) {
		int id=str[i]-'a';
		if (!tr[now].s[id]) {
			tr[now].s[id]=++cnt;
			tr[cnt].f[0]=now;
			tr[cnt].dep=tr[now].dep+1;
			
			for (int i=1;i<=MAXLOG;i++) {
				tr[cnt].f[i]=tr[tr[cnt].f[i-1]].f[i-1];
				if (tr[cnt].f[i]==0) break; } }
		now=tr[now].s[id]; }
	
	pos[x]=now;
	
	return ;
}

int up(int x,int step)
{
	while (step) {
		int up=LOG[step];
		x=tr[x].f[up];
		step-=(1<<up); }
	return x;
}

int LCA(int x,int y)
{
	if (tr[x].dep>tr[y].dep) x=up(x,tr[x].dep-tr[y].dep);
	else y=up(y,tr[y].dep-tr[x].dep);
	if (x==0 || y==0)
		puts("WTF??");
	
	int k=LOG[tr[x].dep];
	while (x!=y) {
		while (k>=0 && tr[x].f[k]==tr[y].f[k]) k--;
		if (k==-1) return tr[x].f[0];
		x=tr[x].f[k]; y=tr[y].f[k]; }
	
	return x;
}

void init()
{
	for (int i=1,now=-1,next=1;i<=MAXL;i++) {
		if (i==next) { now++; next<<=1; }
		LOG[i]=now; }
	
	n=read(),m=read(); cnt=1;
	int sum=0; 
	for (int i=1;i<=n;i++) {
		scanf("\n%s",str); len=strlen(str);
		sum+=len;
		insert(i); }
	
	while (m--) {
		int ty=read();
		if (ty==1) {
			scanf("%s",str); len=strlen(str);
			insert(++n); }
		else {
			int T=read(),ans=0;
			while (T--) {
				int x=read(); //putchar(last[x]); putchar(' ');
				if (ans==0) ans=pos[x];
				else ans=LCA(ans,pos[x]); }
			printf("%d\n",tr[ans].dep); } }
	
	return ;
}

int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	init();
	fclose(stdin);
	fclose(stdout);
	return 0;
} 
