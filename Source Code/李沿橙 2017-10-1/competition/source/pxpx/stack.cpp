#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
int n,ans=0;

int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	scanf("%d",&n);
	if(n<=19)
	{
		if(n==0) ans=1;
		if(n==1) ans=1;
		if(n==2) ans=2;
		if(n==3) ans=5;
		if(n==4) ans=0;
		if(n==5) ans=0;
		if(n==6) ans=6;
		if(n==7) ans=2;
		if(n==8) ans=2;
		if(n==9) ans=4;
		if(n==10) ans=3;
		if(n==11) ans=0;
		if(n==12) ans=0;
		if(n==13) ans=4;
		if(n==14) ans=6;
		if(n==15) ans=6;
		if(n==16) ans=5;
		if(n==17) ans=2;
		if(n==18) ans=0;
		if(n==19) ans=0;
	}
	else
	{
		if(n%7==4||n%7==5)
		ans=0;
		else if(n%7==6||n%7==0)
		ans=6;
		else
		ans=n%7;
	}
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
