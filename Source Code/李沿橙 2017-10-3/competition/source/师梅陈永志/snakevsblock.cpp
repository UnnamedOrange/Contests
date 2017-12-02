#include<bits/stdc++.h>
using namespace std;
#define N 200
int a[N][6],s;
int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=5;j++)
		{
			cin>>a[i][j];
			if(a[i][j]>=0) s+=a[i][j];
		}
	}
	cin>>m;
	cout<<s+4;
	return 0;
}
