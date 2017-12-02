#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int i,j,m,n;
int c,x,l,y,r;
int sum[1005][1005];
int ss[100005];
int s;
int a[100005];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	cin>>n>>m;
	if(n>1000)
	{
		for(i=1;i<=n;i++) cin>>a[i],ss[a[i]]++;
		for(j=1;j<=m;j++)
		{
			cin>>x;
			if(x==1)
			{
				cin>>l>>r>>c;
				if(r-l<=20) 
				{
					s=0;
					for(i=l;i<=r;i++) if(a[i]==c) s++;
					cout<<s<<endl;
				}
				else
				{
					s=0;
					for(i=1;i<=l-1;i++) if(a[i]==c) s++;
					for(i=n;i>=r+1;i--) if(a[i]==c) s++;
					cout<<ss[c]-s<<endl;
				}
			}
			else
			{
				cin>>y;
				swap(a[y],a[y+1]);
			}
		}
	}
	else
	{
		for(i=1;i<=n;i++) sum[0][i]=0;
		for(i=1;i<=n;i++)
		{
			cin>>a[i];
			for(j=1;j<=n;j++)
			{
				sum[i][j]=sum[i-1][j];
			}
			sum[i][a[i]]++;
		}

		for(j=1;j<=m;j++)
		{
			cin>>x;
			if(x==1)
			{
				cin>>l>>r>>c;
				cout<<sum[r][c]-sum[l][c]+(a[l]==c)<<endl;
			}
			else
			{
				cin>>y;
				sum[y][a[y]]--;
				sum[y][a[y+1]]++;
				swap(a[y],a[y+1]);
			}
		}	
	}
	//for(i=1;i<=n;i++)
//	{
	//	for(j=1;j<=n;j++)
//		cout<<sum[i][j]<<' ';
	//	cout<<endl;
//	}
	return 0;
}
