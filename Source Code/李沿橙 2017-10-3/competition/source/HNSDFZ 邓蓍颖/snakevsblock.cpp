#include<bits/stdc++.h>
using namespace std;
struct abc{
	int x,y;
};
int z[210][210],s[210][210],f[8000],things[8000],tot,ans,may[210][210],minn=-9999999/*最小的墙*/,maxn=4/*最多的豆*/,n,m,a[5]={0,0,0,1},b[5]={0,-1,1,0};abc h[40100];//方向：左，右，下，上 
int bfs()
{
	int head=0,tail=1,i;
	h[1].x=1;
	h[1].y=3;
	while(head<tail)
	{
		head++;
		for(i=1;i<=3;i++)
		{
			if(i==2&&may[h[head].x][h[head].y])continue;
			if(h[head].x+a[i]>0&&h[head].x+a[i]<=n&&h[head].y+b[i]>0&&h[head].y+b[i]<=5&&!z[h[head].x+a[i]][h[head].y+b[i]])
			{
				if(i==1&&may[h[head].x+a[i]][h[head].y+b[i]])continue;
				z[h[head].x+a[i]][h[head].y+b[i]]++;
				tail++;
				h[tail].x=h[head].x+a[i];
				h[tail].y=h[head].y+b[i];
				if(s[h[tail].x][h[tail].y]>0)maxn+=s[h[tail].x][h[tail].y];
				else if(s[h[tail].x][h[tail].y]<0)
				{
					tot++;
					things[tot]=-s[h[tail].x][h[tail].y];
				}
			}
		}
	}
}
/*未解决：1，一个豆豆可能被一圈墙围起来，而这些墙可能进不去
2，x个豆豆在一圈墙里，进去可以吃掉豆豆并获得一定分数，但长度可能减少，若长度减少而导致长度不是最小可以到达的墙的倍数，可能反而得分会低？
比如说一圈墙围着一个1的豆豆，现有长度为10，最小的围墙是4，其他都为极大值，而墙外有围墙9，一进一出后获得积分8，长度变为3，
不能再穿过任何围墙，那么积分反而不如直接去找围墙9.
√3，每次选最小的墙撞是不合理的，就比如长度为10，然后有一个围墙9，一个围墙4，显然去围墙9更优，可能解决方案：完全背包*/
int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	int i,j,a,b,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)for(j=1;j<=5;j++)scanf("%d",&s[i][j]);
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		may[a][b]++;
	}
	bfs();
	for(i=1;i<=tot;i++)
		for(j=things[i];j<=maxn;j++)
		{
			if(f[j]<f[j-things[i]]+things[i])f[j]=f[j-things[i]]+things[i];
		}
	printf("%d",f[maxn]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
