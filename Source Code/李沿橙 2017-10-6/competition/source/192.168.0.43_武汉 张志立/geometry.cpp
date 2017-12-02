#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long double x[100005],y[100005];
long double k[100005],b[100005];
long double kk;
long double xx,yy;
long double ax,ay;
int i,j,n,m;
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>x[i];
	}
	for(i=1;i<=n;i++)
	{
		cin>>y[i];
	}
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	for(i=1;i<=n;i++)
	{
		b[i]=y[i];
		k[i]=(-b[i])/x[i];
	}
	cin>>m;
	for(i=1;i<=m;i++)
	{
		cin>>xx>>yy;
		kk=yy/xx;
		int s=0;
		for(j=1;j<=n;j++)
		{
			
			ax=b[j]/(kk-k[j]);
			ay=kk*ax;
			//cout<<ax<<ay;
			if(xx>=ax && yy>=ay) s++;
			else break;
		}
		cout<<s<<endl;
	}
	return 0;
}
