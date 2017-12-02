#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}

long long n,m,k;
int main()
{	
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	n=read();m=read();k=read();
	long long a=n*m%mod;
	a=a*k%mod;
	cout<<a;
	
	return 0;
}
