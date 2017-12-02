#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define pii pair<int,int>

#define debug(...) fprintf(stderr,__VA_ARGS__)

int read()
{
	int ret=0;
	char c=getchar();

	while (c<'0' || c>'9') c=getchar();

	while (c>='0' && c<='9') {
		ret=ret*10+c-'0'; c=getchar(); }

	return ret;
}

const int MAXN=20000,MAXM=100000;

pair<int,pii > front[MAXM+10];

int n,m;

int f[(MAXN<<1)+10];

int find(int x) { if (!f[x]) return x; return f[x]=find(f[x]); }

void init()
{
	n=read(),m=read();

	for (int i=1;i<=m;i++) {
		int x=read(),y=read(),k=read();
		front[i]=mp(k,mp(x,y));	}

	sort(front+1,front+m+1);

	for (int i=m;i>=1;i--) {
		int x=front[i].y.x,y=front[i].y.y;

		if (find(x)!=find(y)) {
			if (find(x+n)!=find(y))
				f[find(x+n)]=find(y);

			if (find(y+n)!=find(x))
				f[find(y+n)]=find(x);	}
		
		else {
			cout<<front[i].x<<endl;
			return ;	}	}

	cout<<0<<endl;

	return ;
}

int main()
{
	freopen("prison.in","r",stdin);
	freopen("prison.out","w",stdout);
	init();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
