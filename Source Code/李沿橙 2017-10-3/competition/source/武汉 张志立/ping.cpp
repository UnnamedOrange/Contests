#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int i,j,k,m,n,a,b;
int l[17][17];
int u[115],v[115];
int bb[115][17];
int bj[115],sum[17];
int ans[17];
int z[17],zb[17];
void dfs(int a,int b,int s)
{
	if(a==b) for(j=1;j<=s-1;j++) bb[i][z[j]]=1;
	else
	for(int j=1;j<=n;j++)
	{
		if(l[a][j] && zb[j])
		{
			z[s]=j;
			zb[j]=false;
			dfs(j,b,s+1);
			z[s]=0;
			zb[j]=true;
		}
	}
}
int main()
{
	//freopen("ping.in","r",stdin);
	//freopen("ping.out","w",stdout);
    cin>>n>>m;
    
	for(i=1;i<=m;i++)
    {
    	cin>>a>>b;
    	l[a][b]=l[b][a]=1;
    }
    
	cin>>k;
    
	for(i=1;i<=k;i++)
    {
    	cin>>u[i]>>v[i];
    }
    
	for(i=1;i<=n;i++)
    {
    	zb[i]=true;
    }
    
	for(i=1;i<=k;i++)
    {
    	dfs(u[i],v[i],1);
    }
    
	for(j=1;j<=k;j++)
    {
    	for(i=1;i<=n;i++)
    	cout<<bb[j][i]<<' ';
		cout<<endl; 
    }
   
   
   
    	
    	
    
    
    
	return 0;
}
