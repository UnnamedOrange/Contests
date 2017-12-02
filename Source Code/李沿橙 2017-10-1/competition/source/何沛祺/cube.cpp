#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<algorithm>
using namespace std;
int s[30010],t,d,n,x,y;
int wz[30010];
int z[30010];
int z1[3001][30010];
char p;
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	cin>>n;
	for(int i=1;i<=30000;i++)
		s[i]=i,z[i]=1,wz[i]=1;
	for(int i=1;i<=3000;i++)
		z1[i][1]=i;
	for(int i=1;i<=n;i++)
	{
		cin>>p;
		if(p=='M')
		{
			cin>>x>>y;
			for(int j=1;j<=z[x];j++)
			{
				z[s[y]]++;
				z1[s[y]][z[y]]=z1[s[x]][j];
				wz[z1[s[x]][j]]=z[s[y]];
				s[z1[s[x]][j]]=s[y];				
			}
		}
		else
		{
			cin>>x;
			cout<<wz[x]-1<<endl;
		}
	}
	return 0;
}
/*
6
M 1 6
C 1
M 2 4
M 2 6
C 3
C 4
*/
