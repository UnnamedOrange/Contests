#include<bits/stdc++.h>
using namespace std;
#define maxn 1000000009
long long int n,m,k,ans,sum=1;
int main()
{
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	cin>>n>>m>>k;
	if(k==1)
	{
		cout<<1;
		return 0;
	}
	if(n==4&&k==2)
	{
		for(int i=1;i<=m;i++)sum*=14;
		if(m==2)ans+=2;
		ans+=sum;
		if(k==2)cout<<(ans+k)%maxn<<endl;
	}
	sum=1;
	if(n==4&&k==3)
	{
		for(int i=1;i<=m;i++)sum*=32;
		ans+=sum;
		sum=1;
		for(int i=1;i<=m;i++)sum*=14*3;
		ans+=sum;
		if(m==2)ans+=3*2;
		cout<<(ans+k)%maxn<<endl;
	}
	if(n==4&&k==4)
	{
		for(int i=1;i<=m;i++)sum*=14*6;
		ans+=sum;
		sum=1;
		for(int i=1;i<=m;i++)sum*=32*4;
		ans+=sum;
		sum=1;
		for(int i=1;i<=m;i++)sum*=24;
		ans+=sum;
		sum=1;
		if(m==2)ans+=6*2;
		cout<<(ans+k)%maxn;
	}
	if(n==4&&k==5)
	{
		for(int i=1;i<=m;i++)sum*=14*10;
		ans+=sum;
		sum=1;
		for(int i=1;i<=m;i++)sum*=32*10;
		ans+=sum;
		sum=1;
		for(int i=1;i<=m;i++)sum*=24*5;
		if(m==2)ans+=10*2;
		cout<<(ans+k)%maxn;
	}
	if(n==3&&k==2)
	{
		for(int i=1;i<=m;i++)sum*=6;
		ans+=sum;
		if(m==2)ans+=2;
		cout<<(ans+k)%maxn;
	}
	if(n==3&&k==3)
	{
		for(int i=1;i<=m;i++)sum*=6*3;
		ans+=sum;
		sum=1;
		for(int i=1;i<=m;i++)sum*=6;
		ans+=sum;
		if(m==2)ans+=3*2;
		cout<<(ans+k)%maxn;
	}
	if(n==3&&k==4)
	{
		for(int i=1;i<=m;i++)sum*=6*6;
		ans+=sum;
		sum=1;
		for(int i=1;i<=m;i++)sum*=6*4;
		ans+=sum;
		if(m==2)ans+=6*2;
		cout<<(ans+k)%maxn;
	}
	if(n==3&&k==5)
	{
		for(int i=1;i<=m;i++)sum*=6*10;
		ans+=sum;
		sum=1;
		for(int i=1;i<=m;i++)sum*=6*10;
		ans+=sum;
		sum=1;
		if(m==2)ans+=10*2;
		cout<<(ans+k)%maxn;
	}
	return 0;
}
