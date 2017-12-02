#include<cstdio>
#include<iostream>

using namespace std;
int sum[410];
int matrix[410][410];
bool special[1000004];
int n,m,k;
int ans=0;
void especially()
{
	int a=matrix[1][1];
	int x=k/a;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(i*j==x)	ans+=(n-i+1)*(m-j+1);
	printf("%d",ans);
	return ;
}

void check(int x1,int y1,int x2,int y2)
{
	int cnt=0;
	for(int i=x1;i<=x2;++i)
		for(int j=y1;j<=y2;++j)
			cnt+=matrix[i][j];
	if(cnt%k==0)	++ans;
	return ;
}

int main()
{
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	
	
	scanf("%d%d%d",&n,&m,&k);//n ÐÐ m ÁÐ 
	
	for(int i=1;i<=400;++i)
	{
		sum[i]=sum[i-1]+i;
	}
	
	if(k==1)	{printf("%d",sum[n]*sum[m]);return 0;}
	int cnt=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			scanf("%d",&matrix[i][j]);
			if(special[matrix[i][j]]==false)
				special[matrix[i][j]]=true,++cnt;
		}
	if(cnt==1)	{especially();return 0;}
	
	for(int i1=1;i1<=n;++i1)
		for(int j1=1;j1<=m;++j1)
			for(int i2=i1;i2<=n;++i2)
				for(int j2=j1;j2<=m;++j2)
					check(i1,j1,i2,j2);
	printf("%d",ans);
	return 0;
}
