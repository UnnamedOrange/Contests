#include<bits/stdc++.h>
using namespace std;
long long fac(int x,int k)
{
	long long sum=x;
	for(int i=1;i<k;i++)
	{
		sum *= x;
		sum %= 998244353;
	}
	return sum;
}
int f(int x)
{
	double sum=1,count=1;
	for(int i=2;i<x;i++)
	{
		int flag=0;
		for(int j=2;j<=i;j++)
		{
			if(x%j==0 && i%j==0)
			{
				flag=1;break;
			}
		}
		if(flag==0){sum+=i;count++;} 
	}
	return (sum/count)*2;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int l,r,k;
	long long sum=0;
	cin>>l>>r>>k;
	for(int i=l;i<=r;i++)
	{
		sum += fac(f(i)%998244353,k);
      	sum %= 998244353;
	}
	cout<<sum;
	fclose(stdin);fclose(stdout);
}
