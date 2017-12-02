#include <bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
char a[205];int ans=1;
int main()
{	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	cin>>a;
	for(int i=0,j=strlen(a);i<j-4;i++)
	{
		if(a[i]==a[i+2]&&a[i]==a[i+4]&&a[i+1]==a[i+3])ans++;
	}
	cout<<ans%5;
	return 0;
}
