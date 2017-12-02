#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int a[1001][1001];
int main()
{
	freopen("stack.in","r",stdin);
freopen("stack.out","w",stdout);
	long long  n,m;
	cin>>n;
	a[1][1]=1;
	for(int i=2;i<=n;i++)
	{
		m=0;
	for(int j=i;j>=2;j--)
	{
		m+=(a[i-1][j-1])%700000;
	a[i][j]=m; 
	}
	a[i][1]=m;
	}
	m=0;
	for(int j=1;j<=n;j++)
	m=(m+a[n][j]%7)%7;
	cout<<m;
return 0;

}

