#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int i,j;
long long k;
int t;
long long s;
int ma[405][405];
long long sum[405][405];
int m,n;
int x,y,xx,yy;
int main()
{
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	cin>>n>>m>>k;
	for(i=0;i<=n;i++) sum[i][0]=0;
	for(j=0;j<=m;j++) sum[0][j]=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++) 
		{
			cin>>ma[i][j];
			sum[i][j]=sum[i-1][j]+sum[i][j-1]+ma[i][j]-sum[i-1][j-1];
		}
	}
//	for(i=0;i<=n;i++)
//	{
	//	for(j=0;j<=m;j++)
	//	cout<<sum[i][j]<<' ';
	//	cout<<endl;
//	}
	for(x=1;x<=n;x++)
	{
		for(y=1;y<=m;y++)
		{
			for(xx=x;xx<=n;xx++)
			{
				for(yy=y;yy<=m;yy++)
				{
					
						s=0;
						s=sum[xx][yy]-sum[xx][y-1]-sum[x-1][yy]+sum[x-1][y-1];
						if(s%k==0) 
						{
							//cout<<x<<' '<<y<<' '<<xx<<' '<<yy<<' '<<s;
							//cout<<endl;
							t++;
						}
				}
			}
		}
	}
	cout<<t;
	
	return 0;
}

