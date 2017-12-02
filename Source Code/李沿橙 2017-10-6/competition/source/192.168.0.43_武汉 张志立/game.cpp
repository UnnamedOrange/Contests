#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int i,j,n,m;
int x,h;
int l,r;
long long c,k;
long long a[50005];
long long s=1,ma;
const long long mm=1000000007;
int main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(h=1;h<=m;h++)
	{
		cin>>x;
		if(x==1)
		{
			cin>>l>>r>>c;
			for(i=l;i<=r;i++)
				a[i]+=c;
		}
		if(x==2)
		{
			cin>>l>>r;
			for(i=l;i<=r;i++)
				a[i]=-a[i];
		}
		if(x==3)
		{
			cin>>l>>r>>k;
			if(k==1)
			{
				s=0;
				for(i=l;i<=r;i++)
				{
					s=s+a[i];
				}
				if(s>=0)
				  cout<<s<<endl;
				else
				{
					while(s<0) s+=mm;
					cout<<s<<endl;
				}
			}
			if(k==2)
			{
				s=0;
				for(i=l;i<=r;i++)
				{
					for(j=l;j<=i-1;j++)
					s=s+a[i]*a[j];
				}
				if(s>=0) cout<<s%mm<<endl;
				else 
				{
					while(s<0) s=s+mm;
					cout<<s<<endl;
				}
			}
			if(k>=3)
			{
				s=1;
				for(i=l;i<=r;i++)
				s=s*a[i];
				if(s>=0) cout<<s%mm<<endl;
				else 
				{
					while(s<0) s=s+mm;
					cout<<s<<endl;
				}
			}
			
			
		}
	//	for(i=1;i<=n;i++)
	//	   cout<<a[i]<<' ';
	//	   cout<<endl;
	}
	return 0;
}
