#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int f[1500];
int main()
{
	int n,i,j;
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		f[i]=f[i-1]+1;
		for(j=2;j<i;j++)
			f[i]=(f[i]+f[i-j+1])%7;
	}
	printf("%d",f[n]);
	return 0;
}
