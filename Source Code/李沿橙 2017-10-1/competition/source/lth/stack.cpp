#include <bits/stdc++.h>
using namespace std;
int n,book[1001],a[1001],p[100001],ans;
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-') y=1;c=getchar();}
	while(c>='0'&&c<='9') {
	x=x*10+c-'0';c=getchar();}
		return x*y;
	}
void prime(){
	for(int i=2;i*i<=1000001;i++)
	{if(p[i]) continue;
	for(int j=i*i;j<=1000001;j+=i) p[j]=1;}
}
int fastm(int a,int b,int c){
	int ans=1;
	while(b){
		if(b%2==0) ans=ans*a%7;a=a*a%7;b=b/2;}
		return ans;
}
int count(int x,int prime){
	int z=0;
	while(x){
		z+=x/prime;x=x/prime;}
		return z;
}
int main(){
	//freopen("stack.in","r",stdin);
	//freopen("stack.out","w",stdout);
	cin>>n;
	int sum=0;
	prime();for(int i=1;i<=1000001;i++) if(!p[i]) a[sum++]=i;
	for(int i=0;i<=sum&&a[i]<=2*n;i++){
	int cnt=count(n*2,a[i])-count(n,a[i])-count(2*n-n,a[i]);
	ans=ans*fastm(a[i],cnt,7);}
	cout<<ans<<endl;
	return 0;
	}
