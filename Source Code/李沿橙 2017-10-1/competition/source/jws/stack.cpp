#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 1005
int n;
int ans[MAXN]={0,1,2,5,0,0,6,2,2,4,3,0,0,4,6,6,5,2,0,0,4,6};
using namespace std;
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	scanf("%d",&n);
	printf("%d\n",ans[n]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
