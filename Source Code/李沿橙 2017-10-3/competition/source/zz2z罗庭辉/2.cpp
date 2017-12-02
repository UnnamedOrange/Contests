#include <bits/stdc++.h>
#define inf 10000000
using namespace std;
stack <int> q[10001];
int times=1;int idd;
int n,m,k,f[3001][3001],book[3000][3000],a[3001][3001],b[3001];
void dfs(int x,int y,int times){
	if(idd==0) q[times].push(x);
	for(int i=1;i<=n;i++)
	if(f[x][i]==1&&book[y][i]==0){
	if(i==y) {q[times].push(y);break;}	
	else {book[x][i]=book[i][x]=1;q[times].push(i);b[times]++;idd=1;dfs(i,y,times);}} 
	else return;
	}
int main(){
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
	{
		if(i==j) f[i][j]=0;
		else f[i][j]=f[j][i]=inf;
	}	
	for(int i=1;i<=m;i++)
	{
		int t,w;
	cin>>t>>w;
	f[t][w]=f[w][t]=1;}
	/*for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			for(int i=1;i<=n;i++)
				{
					for(int j=1;j<=n;j++)
					cout<<f[i][j];
					cout<<endl;
				}*/
	int t1,ans=1000000;cin>>t1;			
	for(int i=1;i<=t1;i++)
	{
	int t,w;
	cin>>t>>w;
	memset(book,0,sizeof(book));
	idd=0;
	dfs(t,w,times);
	times++;	
	}
	times--;
	int x;
	int mins=1000000;
	for(int i=1;i<=times;i++){
	if(mins>b[i]) {mins=b[i]; x=i;}
	for(int j=1;j<=b[i];j++)
	{cout<<q[i].top();a[i][j]=q[i].top();q[i].pop();}
	}
	cout<<mins<<endl;
	for(int i=1;i<=mins;i++)
	cout<<a[x][i]<<" ";
	return 0;
}
