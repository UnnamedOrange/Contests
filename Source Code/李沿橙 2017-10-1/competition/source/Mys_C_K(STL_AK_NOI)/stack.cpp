#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 7
#define N 1010
using namespace std;
int f[N];
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	int n;scanf("%d",&n);
	f[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
			(f[i]+=f[j]*f[i-j-1])%=mod;
	printf("%d\n",f[n]);return 0;
}
