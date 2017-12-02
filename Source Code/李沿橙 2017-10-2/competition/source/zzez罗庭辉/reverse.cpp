#include <bits/stdc++.h>
#define inf 10000000
using namespace std;
string s;
int ans=inf;
int a[100001],b[100001],c[100001];
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();
	}
return x*y;	
}
int main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	cin>>s;
	int len=s.size();
	for(int i=1;i<=len;i++){
		if(s[i-1]=='1') b[i]=b[i-1]+1;
		else b[i]=b[i-1];	}
	for(int i=len;i>=1;i--){
		if(s[i-1]=='0') a[i]=a[i+1]+1;
		else a[i]=a[i+1];}
	for(int i=0;i<=len;i++)
	{
		c[i]=b[i]+a[i+1];
	}
	for(int i=0;i<=len;i++)
	ans=min(ans,c[i]);
	cout<<ans<<endl;
		return 0;
}
