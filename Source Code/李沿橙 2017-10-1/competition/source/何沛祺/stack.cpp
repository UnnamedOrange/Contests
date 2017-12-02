#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<algorithm>
using namespace std;
int a[401000][2],n,total;
int c[4]={0,1,4,5};
bool b[1010]={0};
void f(int x)
{
	int head=0,tail=1,ans=0;
	for(int j=1;j<=n;j++)
	{
		memset(a,0,sizeof(a));
		a[0][0]=j;
	
	while(head<tail)
	{
		memset(b,0,sizeof(b));
		b[j]=1;
		if(a[head][1]==x)
		{
			total++;
			total%=7;
			head++;
				if(head>400000)
		head=0;
			continue;
		}
	for(int i=1;i<=n;i++)
	{
		if(b[i]==0)
		{
			if(a[head][0]-i<=1)
			{
					b[i]=1;
					a[tail][0]=i;
					a[tail][1]=a[head][1]+1;
					tail++;
					if(tail>400000)
						tail=1;
			}		
		}
	}
	head++;
	if(head>400000)
		head=0;
	}
	}
}
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	cin>>n;
	if(n>3)
	{
	total=n%7;
	for(int i=2;i<=n;i++)
	{
		memset(a,0,sizeof(a));
 		f(i);
	}
	cout<<total;
	}
	else
		cout<<c[n];
	return 0;
}

