#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
string k;
int b[100005],c[100005];
int ans=1000000;
int main()
{	
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	cin>>k;
	for(int i=0,j=k.length();i<j;i++)
	{
		if(k[i]=='1')b[i+1]=b[i]+1;
		else b[i+1]=b[i];
		if(k[j-1-i]=='0')c[j-i]=c[j+1-i]+1;
		else c[j-i]=c[j+1-i];
	}
	/*for(int i=1,j=k.length();i<=j;i++)cout<<b[i]<<" ";
	cout<<endl;
	for(int i=1,j=k.length();i<=j;i++)cout<<c[i]<<" ";
	*/
	for(int i=1,j=k.length();i<=j-1;i++)
	{
		ans=min(ans,b[i]+c[i+1]);
	}
	printf("%d\n",ans);
	return 0;
}
