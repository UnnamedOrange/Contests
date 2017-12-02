#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k;
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	scanf("%d%d",&n,&k);
	int t1,t2=0,t3=10000000;
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&t1);
		if(!(t2&1))
		{
			if(t1>t3)t3=t1;
			else if(t3-t1>=k)t2+=1,t3=t1;
		}
		else
		{
			if(t1<t3)t3=t1;
			else if(t1-t3>=k)t2+=1,t3=t1;
		}
	}
	printf("%d\n",t2);
	return 0;
}
