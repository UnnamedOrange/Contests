#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;
int n,k,a[2000004],last=-100000000;
bool oushu;
int ans=0;
int read()
{
	int x;char ch;
	while(ch=getchar(),ch<'0'||ch>'9');
	x=ch-'0';
	while(ch=getchar(),ch>='0'&&ch<='9')
		x=x*10+ch-'0';
	return x;
}

void input()
{
	n=read();k=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	return;
}

int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	input();
	for(int i=1;i<n;++i)
	{
		if(!oushu&&a[i]<=a[i+1])
		{
			if(abs(a[i]-last)>=k)
			{
				++ans;
				last=a[i];
				oushu=1-oushu;
			}
		}
		else if(oushu&&a[i]>=a[i+1])
		{
			if(abs(a[i]-last)>=k)
			{
				++ans;
				last=a[i];
				oushu=1-oushu;
			}
		}
	}
	if(!oushu&&last-a[n]>=k)
	{
		++ans;
	}
	else if(oushu&&a[n]-last>=k)
	{
		++ans;
	}
	printf("%d",ans);
	return 0;
}
