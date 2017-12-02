#include<cstdio>
#include<iostream>

using namespace std;
int n,rest,last=0;
bool book[1004];
int cnt=0;

bool che(int a,int b)
{
	for(int i=b+1;i<a;++i)
	{
		if(book[i]==false)	return false;
	}
	return true;
}

void search(int now,int last)
{
	if(now==n+1)
	{
		cnt++;
		cnt%=7;
		return;
	}
	for(int i=1;i<=n;++i)
	{
		if(book[i]==false&&(last==0||last-i<2||che(last,i)))
		{
			book[i]=true;
			search(now+1,i);
			book[i]=false;
		}
	}
	return;
}

int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	scanf("%d",&n);
	rest=n;
	search(1,0);
	printf("%d",cnt);
	return 0;
}
