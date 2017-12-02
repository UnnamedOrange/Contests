#include<bits/stdc++.h>
using namespace std;
int a[1000001],b[1000001];
int n,m;
int main()
{
	ios::sync_with_stdio(false);	
	cin>>n>>m;
	int k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>k;
		for(int i=1;i<=n;i++)
		{
			b[i]=a[i];
		}
		
	}
}
