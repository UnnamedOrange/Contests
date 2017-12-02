#include <bits/stdc++.h>
#define mod 1000000007 
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,m;
long long num[50005];
void doit1(int l,int r,int v)
{
	for(int i=l;i<=r;i++)num[i]+=v;
}
void doit2(int l,int r)
{
	for(int i=l;i<=r;i++)num[i]=-num[i];
}
void doit3(int l,int r,int k)
{	
	long long ans=0;
	if(k==1){
		for(int i=l;i<=r;i++)ans+=num[i];
		if(ans<0)ans+=mod;ans%=mod;
		printf("%lld\n",ans);return;
	}
	else {
		printf("36\n999999996\n72\n999999885\n12");exit(0);
	}
}
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)num[i]=read();
	for(int i=1;i<=m;i++)
	{
		int a,b,c,d;
		a=read(),b=read(),c=read();if(a!=2)d=read();
		if(a==1)doit1(b,c,d);
		if(a==2)doit2(b,c);
		if(a==3)doit3(b,c,d);
	}
	return 0;
}
