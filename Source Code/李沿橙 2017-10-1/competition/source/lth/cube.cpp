#include <bits/stdc++.h>
using namespace std;
stack <int> a[30001];
stack <int> q;
int b[30001],c[30001],sum;
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0') {
	if(c=='-') y=1; c=getchar();	
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();
	}
	return x*y;
}
inline int put(int t,int w){
	while(!a[t].empty()){
	c[sum++]=a[t].top();
	b[a[t].top()]=w;	
	a[t].pop();	
	}
	for(int i=sum-1;i>=0;i--)
	{
		a[t].push(c[i]);a[w].push(c[i]);
	}
	memset(c,0,sizeof(c));
	sum=0;
}
inline int count(int id,int num){
	int x=0,sum=0;
	while(!a[id].empty())
	{c[sum++]=a[id].top();
	if(a[id].top()==num) x=sum;
	a[id].pop();
	}
	cout<<sum-x<<endl;
	for(int i=sum-1;i>=0;i--)
{
	a[id].push(c[i]);
	}
	memset(c,0,sizeof(c));
	sum=0;
}
int n;
int main(){
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) b[i]=i;
	for(int i=1;i<=n;i++) a[i].push(i);
	for(int i=1;i<=n;i++){
		char c; cin>>c;
	if(c=='M'){
		int t,w;
		t=read();w=read();
		put(b[t],b[w]);
	} 	
	else {
	int ans;ans=read();
	count(b[ans],ans);
	}		
	}
	return 0;
}
