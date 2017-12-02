#include<bits/stdc++.h>
#define mod 998244353
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
long long l,r,k,ans=0;
long long fastm(int x)
{
	int y=k,re=1,s=x;
	while(y){
		if(y%2)re*=s,re%=mod;
		s*=s,s%=mod;
		y/=2;
	}
	return re;
}
int main()
{	
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	l=read();r=read();k=read();
	for(int i=l;i<=r;i++){
		if(i==1){ans+=fastm(2);ans%=mod;continue;}
		ans+=fastm(i);ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
