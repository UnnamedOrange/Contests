#include<bits/stdc++.h>
using namespace std;
queue<int>work;
stack<int>tem;
int w[26],p[26],t,n,sum;
int init()
{
	while(!work.empty())work.pop();
	sum=0;
}
int read()
{
	int x=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int check(int num)
{
	int k[26],t[26],cont=0;
	bool flag;
	while(!work.empty())work.pop();
	for(int i=1;i<=24;i++)k[i]=w[i],t[i]=p[i];
	for(int i=1;i<=24;i++)
	{
		while(!work.empty()&&i-work.front()>=8)work.pop();
		k[i]-=work.size();
		if(k[i]>0)
		{
			flag=true;
			for(int j=i;j>=max(i-7,1);j--)
			{
				while(t[j]&&flag)
				{
					k[i]--,t[j]--;
					cont++;
					tem.push(j);
					if(!k[i])flag=false;
				}
				if(!flag)break;
			}
			while(!tem.empty())
			{
				int tem2=tem.top();
				tem.pop();
				work.push(tem2);
			}
			if(k[i]>0) return 0;
		}
		if(cont>num)return 0;
	}
	return 1;
}
int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	t=read();
	while(t--)
	{
		init();
		for(int i=1;i<=24;i++)w[i]=read();
		for(int i=1;i<=24;i++)
		{
			cin>>p[i];
			sum+=p[i];
		}
		int l=0,r=sum,yes=0;
		while(l<r)
		{
			int mid=(l+r)/2;
			int can=check(mid);
			if(!can)l=mid+1;
			else r=mid;
		}
		int can=check(l);
		if(can)printf("%d\n",l);
		else printf("-1");
	}
	return 0;
}
