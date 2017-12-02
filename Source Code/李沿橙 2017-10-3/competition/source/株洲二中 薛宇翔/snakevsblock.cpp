#include <bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n;
int num[205][6];
int m;
bool nu[205][6];
int main ()

{	
	freopen("snakevssblock.in","r",stdin);
	freopen("snakevssblock.out","w",stdout);	
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=5;j++)num[i][j]=read();
	m=read();
	for(int i=1;i<=m;i++)nu[read()][read()]=true;
	int tans=0,ji;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=5;j++){
			if(num[i][j]>0)tans+=num[i][j];
			else {ji=i;break;}
		}	
	}
	int kkk=0;
	for(int i=ji;i<=n;i++)
	{	int kk=num[i][1]+num[i][2]+num[i][3]+num[i][4]+num[i][5];
		if(tans-kk>=0)tans-=kk,kkk+=kk;
		else {
			for(int j=1;j<=5;j++)
			if(tans-num[i][j]>=0)tans-=num[i][j],kkk+=num[i][j];
		}
	}
	cout<<kkk;
	return 0;
}
