#include<bits/stdc++.h>
using namespace std;
long long sum;
double S_i(int x)
{
	double s=(x-1)*x/2,t=x-1;
	for(int j=2;j<x;j++)
	{
		for(int i=2;i<=j;i++)
		{
			if(j%i==0&&x%i==0)
			{
				s-=j;
				t--;
				break;
			}
		}
	}
	return s/t;
}
long long ksm(double x,int k)
{
	long long t=x;
	long long v=t;
	for(int i=1;i<k;i++)
	{
		t=v*t%998244353;
	}
	return t;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int l,r,k;
	cin>>l>>r>>k;
	for(int i=l;i<=r;i++)
	{
		sum+=(ksm(S_i(i)*2,k)%998244353);
		sum=sum%998244353;
	}
	long long m=sum;
	cout<<m%998244353;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
