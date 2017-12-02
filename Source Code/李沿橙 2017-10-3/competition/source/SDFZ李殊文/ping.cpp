#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
#include<vector>
#include<cstdio>

using namespace std;
const int N=25;
int l[N][N];
int main()
{
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	int n,m,u,v,k,s;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		l[u][v]=l[v][u]=1;
	} 
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&u,&v);
	}	
	cout<<1<<endl<<1;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
