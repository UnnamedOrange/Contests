#include <cmath>
#include <queue>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100000
#define ll long long
using namespace std;
inline int read() 
{ 
    int x=0,f=1;char ch=getchar(); 
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();} 
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} 
    return x*f; 
}
int n,m;
int main()
{
	srand(time(0));
	freopen("bad7.in","w",stdout);
	n=200000,m=200000;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++)
	{
		int tmp=rand()%1000+1;
		if(rand()%2==0)tmp=-tmp;
		cout<<tmp<<' ';
	}
	for(int i=1;i<=20000;i++)
	{
		int opt=3;
		cout<<opt<<' '<<1<<' '<<n-i<<endl;
	}
	for(int i=20000+1;i<=50000;i++)
	{
		int opt=3;
		int l=rand()%n+1,r=rand()%n+1;
		if(l>r)swap(l,r);
		cout<<opt<<' '<<l<<' '<<r<<endl;
	}
	for(int i=50001;i<=m;i++)
	{
		int opt=6;
		if(opt==1||opt==2)
		{
			int x=rand()%n+1;
			int v=rand()%1000+1;
			if(rand()%2==0)v=-v;
			cout<<opt<<' '<<x<<' '<<v<<endl;
		}
		else 
		{
			int l=rand()%n+1,r=rand()%n+1;
			if(l>r)swap(l,r);
			cout<<opt<<' '<<l<<' '<<r<<endl;
		}
	}
}