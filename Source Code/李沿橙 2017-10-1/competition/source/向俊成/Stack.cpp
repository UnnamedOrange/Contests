#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int s=0,n;
int main()
{
	freopen("Stack.in","r",stdin);freopen("Stack.out","w",stdout);
	int i,j,k,m;
	scanf("%d",&n);
	if(n==0)printf("0\n");
	else if(n%9==1)printf("1\n");
	else if(n%9==2)printf("2\n");
	else if(n%9==3)printf("5\n");
	else if((n%9==4)||(n%9==5))printf("0\n");
	else if(n%9==6)printf("5\n");
	else if(n%9==7)printf("6\n");
	else if(n%9==8)printf("2\n");
	else if(n%9==0)printf("3\n");
	return 0;
}
