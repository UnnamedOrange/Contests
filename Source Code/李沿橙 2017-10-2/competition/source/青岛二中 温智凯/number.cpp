#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
const int MAXN=1e5+10;
int a[2100];
bool b[10];
int main()
{
	int i,j,k,m,n;
	long long ans,l;
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	memset(a,0,sizeof(a));
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		memset(b,0,sizeof(b));
		m=i;
		while(m>0)
		{
			b[m%10]=true;
			m/=10;
		}
		m=0;
		for (j=0;j<=9;j++)
		{
			if (b[j]) m+=1<<j;
		}
		a[m]++;
	}
	ans=0;
	for (i=1;i<=2050;i++)
	{
		if (a[i]>1)
		{
			l=a[i];
			ans+=l*(l-1)/2;
		
		}
	}
	printf("%lld",ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}

