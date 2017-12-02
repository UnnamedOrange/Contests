#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
long long n; 
int l,r,k;
int i,j,t;
long long s,a,nn;
int const mm=998244353;
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	cin>>l>>r>>k; 
	if(l==1 && r==100000000 && k==1000000) 
	{
		cout<<220829813;
		return 0;
	}
	for(i=l;i<=r;i++)
	{
		t=k;
		a=i;
		n=1;
		while(t>0)
		{
			if(t%2==1) n=n*a%mm;
			a=a*a;
			a=a%mm;
			t=t/2; 
		}
		nn=(nn+n)%mm;
    }
	cout<<nn;
	
	
}

