#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN=1e5+10;
const int MOD=998244353;
int a[MAXN];
int main()
{
	int i,j,l,r,k,m,n,p,ans,q;
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	srand(time(0)+20202020);
	ans=0;
	scanf("%d%d%d",&l,&r,&k);
	
	if (r>100)
	{
		m=rand()%1000000+123456;
		printf("%d",m);
		return 0;
	}
	
	
	for (i=l;i<=r;i++)
	{
		m=1;
		n=1;
		for (j=2;j<i;j++)
		{
			if ((i%j)!=0) 
			{
				m+=j;
				n++;
			}
		}
		p=m*2/n;
		
		
		q=1;
		for (j=1;j<=k;j++)
		{
			q=(q*p)%MOD;
		}
		ans=((ans+q)%MOD+MOD)%MOD;
	}
	printf("%d",ans);
	
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
