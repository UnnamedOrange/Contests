#include <cstring>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int Mod=998244353;
const int MAXK=1000000;

int power(int x,int k)
{
	int ret=1;
	while (k) {
		if (k&1) ret=1LL*ret*x%Mod;
		x=1LL*x*x%Mod; k>>=1; }
	return ret;
}

int k;

int f[MAXK+10];

int pre[MAXK+10],suf[MAXK+10];

int jc[MAXK+10],K[MAXK+10];

int cnt(int n)
{
	if (n==0) return 0;
	int ans=0;
	if (n<=k+10 || n<=MAXK) {
		for (int i=1;i<=n;i++) ans=(K[i]+ans)%Mod; }
	else {
		pre[0]=1;
		for (int i=1;i<=k+2;i++) pre[i]=1LL*pre[i-1]*(n-i)%Mod;
		
		suf[k+3]=1;
		for (int i=k+2;i>=1;i--) suf[i]=1LL*suf[i+1]*(n-i)%Mod;
		
		int l=k+1,r=0,flag=((k+1)&1)?(-1):(1);
		for (int i=1;i<=k+2;i++) {
			int s=1LL*pre[i-1]*suf[i+1]%Mod,m=1LL*(flag*jc[l]+Mod)*jc[r]%Mod;
			ans=(1LL*f[i]*s%Mod*power(m,Mod-2)%Mod+ans)%Mod;
			l--; r++; flag*=-1; } }
	ans=((ans+K[2])%Mod-1+Mod)%Mod;
	return ans;
}

int L,R;

void init()
{
	cin>>L>>R>>k;
	for (int i=1;i<=MAXK+5;i++) K[i]=power(i,k);
		
	jc[0]=1;
	for (int i=1;i<=k+2;i++) jc[i]=1LL*jc[i-1]*i%Mod;
	for (int i=1;i<=k+2;i++) f[i]=(f[i-1]+K[i])%Mod;
	
	cout<<(cnt(R)-cnt(L-1)+Mod)%Mod;
	return ;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	init();
	fclose(stdin);
	fclose(stdout);
	//fprintf(stderr,"%.3lf\n",1.0*clock()/(1.0*CLOCKS_PER_SEC));
	return 0;
}
