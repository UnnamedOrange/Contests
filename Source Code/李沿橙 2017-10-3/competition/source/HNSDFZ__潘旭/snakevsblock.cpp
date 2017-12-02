#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;
int n,m,x,y;
int box[200+10][5+1],dp[200+10][5+1],sd[200+10][4+1];

int main()
{
	//freopen("snakevsblock.in","r",stdin);
	//freopen("snakevsblock.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d%d%d%d%d",&box[i][1],&box[i][2],&box[i][3],&box[i][4],&box[i][5]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		sd[x][y]=1;
	}
	for(int t=1;t<=n;t++)
	for(int i=1;i<=n;i++)
	{
		if(sd[t][i])
	}
	//fclose(stdin);
	//fclose(stdout);
}
