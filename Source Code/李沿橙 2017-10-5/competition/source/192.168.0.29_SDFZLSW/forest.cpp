#include<iostream>
#include<cstdio>
using namespace std;
const int N=10010,m=1000000007;
int n,a[N]={0},mp[N][N]={0},x[N],y[N]; 
int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);	
	int u,v,k;	
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);	
	for(int i=1;i<n;i++) 
	{	
		scanf("%d%d",&u,&v);
		mp[u][v]=mp[v][u]=1;
		x[i]=u;
		y[i]=v;
	}
	for(int i=1;i<n;i++)
	{
		scanf("%d",&k);
		
	}	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
