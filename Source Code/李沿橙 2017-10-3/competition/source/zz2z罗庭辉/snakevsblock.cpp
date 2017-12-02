#include <bits/stdc++.h>
using namespace std;
int n,ans,m;
int main(){
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=5;j++)
	{int t;cin>>t;if(t>=0) ans+=t;}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int t,w;
		cin>>t>>w;
	}
	cout<<ans<<endl;
	return 0;
}
