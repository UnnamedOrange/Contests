#include<iostream>
#include<cstdio>
#include<cstring>

#define N 10001
#define mod 7

using namespace std;
int n,ans;int h[N];

int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	scanf("%d",&n);
	h[1]=1;h[2]=2;
	for(int i=3;i<=n;i++) h[i]=((i-1)*h[i-1]%mod+1)%mod;
	printf("%d\n",h[n]);
	fclose(stdin);fclose(stdout);
	return 0;
}
