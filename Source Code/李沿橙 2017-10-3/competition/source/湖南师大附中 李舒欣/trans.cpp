#include<bits/stdc++.h>
using namespace std;
int a[1007000];
long long k,n;
int read()
{
	char c;
	int x,w=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')w=-1;
		c=getchar();
	}
	return c-'0';
}
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(cin>>n>>k)
	{
		int t=0;
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n&&t<k;i++)
		{
			if(a[i]==2&&a[i+1]==3)
			{
				t++;
				if(i%2)a[i+1]=2;
				else
				{
					a[i]=3;
					i-=2;
				}
			}
		}
		for(int i=1;i<=n;i++)cout<<a[i];
		cout<<endl;
	}
	return 0;
}
