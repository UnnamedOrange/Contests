#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	if(n<100) return !printf("%d\n",0);
	else printf("T-shirt我要和出题人同款的QwQ!\n");
	return 0;
}
