#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>
using namespace std;
int number[10000004];
bool book[14];
int ans=0,n;
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int temp=i;
		int tnum=0;
		for(int j=0;j<10;++j)
			book[j]=false;
		while(temp)
		{
			int t=temp%10;
			if(book[t]==false)
				number[i]+=pow(2,t);
			book[t]=true;
			temp/=10;
		}
	}
	for(int i=1;i<n;++i)
	{
		for(int j=i+1;j<=n;++j)
		{
			if(number[i]==number[j])
				++ans;
		}
	}
	printf("%d",ans);
	return 0;
}
