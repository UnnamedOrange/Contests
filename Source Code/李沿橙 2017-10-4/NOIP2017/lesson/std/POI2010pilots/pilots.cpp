#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

#define Max(a,b) ((a)>(b)?(a):(b))

int read()
{
	int ret=0;
	char c=getchar();

	while (c<'0' || c>'9') c=getchar();

	while (c>='0' && c<='9') {
		ret=ret*10+c-'0'; c=getchar(); }

	return ret;
}

const int MAXN=3000000;

int q[MAXN+10];

int lmin[MAXN+10];
int l1,r1;

int lmax[MAXN+10];
int l2,r2;

int n,k,ans;

void init()
{
	k=read(); n=read();

	for (int i=1;i<=n;i++) q[i]=read();

	r1=r2=-1;

	int cnt=1;

	for (int i=1;i<=n;i++) {
		while (l1<=r1 && q[i]<=q[lmin[r1]]) r1--; lmin[++r1]=i;

		while (l2<=r2 && q[i]>=q[lmax[r2]]) r2--;	lmax[++r2]=i;

		while (q[lmax[l2]]-q[lmin[l1]]>k)
			if (lmax[l2]<lmin[l1]) { cnt=lmax[l2]+1; l2++; } else { cnt=lmin[l1]+1; l1++; }
		
		ans=Max(ans,i-cnt+1);	}

	cout<<ans;

	return ;
}

int main()
{
	freopen("pilots.in","r",stdin);
	freopen("pilots.out","w",stdout);
	init();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
