#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int p=998244353;
int a[10000002],ys[10000002];
int f[101],prime[1000005];
int ksm(int x,int k)
{
	f[0]=x;
	int t,ans=1,i=0;
	for(i=1;(1<<i)<=k;i++)
		f[i]=(long long)f[i-1]*f[i-1]%p;
	i=0;
	while(k>0)
	{
		t=(k&1);
		k=(k>>1);
		if(t==1)
			ans=(long long)ans*f[i]%p;
		i++;
	}
	return ans;
}
void shai(int n)
{
	int cnt=0,i,j;
	for(i=1;i<=n;i++)
		ys[i]=1;
	for(i=2;i<=n;i++)
	{
		if(ys[i]==1)
			prime[++cnt]=i;
		for(j=1;j<=cnt;j++)
		{
			if(i*prime[j]>n)
				break;
			ys[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int l,r,k,i,ans;
	scanf("%d%d%d",&l,&r,&k);
	if(r>=10000000)
	{
		for(i=l;i<=r;i++)
			ans=(ans+ksm(i,k))%p;
		printf("%d",ans);
		return 0;
	}
	shai(r);
	for(i=1;i<=r;i++)
	{
		if(ys[i]==1)
			a[i]=ksm(i,k)%p;
		else
			a[i]=(long long)a[ys[i]]*a[i/ys[i]]%p;
	}
	for(i=l;i<=r;i++)
		ans=(ans+a[i])%p;
	printf("%d",ans);
	return 0;
}
