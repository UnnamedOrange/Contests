#include<bits/stdc++.h>
#define M 1000005
#define lol long long 
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,m,k;
int num[M];
lol num1[M];
void doit()
{	
	for(int i=1;i<=n;i++)num1[i]=num[i]-k;
	for(int i=1;i<=n;i++)num1[i]=num1[i]+num1[i-1];
	if(num1[n]>=0){printf("%d ",n);return;}
	map<int ,int >a;int ans;
	for(int i=1;i<=n;i++){
	if(!a[num[i]])a[num[i]]=i;
	else ans=max(ans,i-a[num[i]]);
	}
	printf("%d",ans);return;
}
int main()
{	
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int Max=0;
	n=read();m=read();
	for(int i=1;i<=n;i++)num[i]=read(),Max=max(Max,num[i]);
	
	for(int i=1;i<=m;i++)
	{
		k=read();
		if(k>Max){cout<<0<<" ";continue;}
		doit();
	}
	return 0;
}
