#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctime>
#define MAXN 205
int n,m,ans=0;
int a[MAXN][7];
int tmpa[MAXN][7];
int h[MAXN*7];
using namespace std;

struct EDGE
{
	int to;
	int next;
	int s;
	int f;
}e[MAXN*5*3];

int cnt=0;
void ADDE(int from,int to)
{
	cnt++;
	e[cnt].to=to;
	e[cnt].next=h[from];
	h[from]=cnt;
}

void work_rand()
{
	int x=1,y=3,num=3;
	int tot=4,poi=0;
	while(1)
	{
		int tmp=0,tmpx=0;
		int to[5],cntto=0;
		for(int i=h[num];i;i=e[i].next)
		{
			if(e[i].f==0)
			{
				cntto++;
				to[cntto]=e[i].to;
			}
		}
		tmp=rand()%cntto+1;
		tmpx=rand()%5+1;
		while(tmpx!=1 && tmp==1) tmp=rand()%cntto+1;
		int tox=to[tmp]/5+1,toy=to[tmp]%5;
		if(toy==0)
		{
			toy=5;
			tox--;
		}
		if(tox>n) break;
		if(tmpa[tox][toy]>0)
		{
			tot+=tmpa[tox][toy];
		}
		else if(tmpa[tox][toy]<0)
		{
			if(tot>-tmpa[tox][toy])
			{
				tot+=tmpa[tox][toy];
				poi-=tmpa[tox][toy];
			}
			else break;
		}
		x=tox;
		y=toy;
		num=5*(x-1)+y;
		tmpa[x][y]=0;
	}
	if(poi>ans) ans=poi;
}

int main()
{
	freopen("snakevsblock.in","r",stdin);
	freopen("snakevsblock.out","w",stdout);
	srand(time(NULL));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=5;j++)
		{
			scanf("%d",&a[i][j]);
			if(j!=5) ADDE(5*(i-1)+j,5*(i-1)+j+1);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=4;j++)
		{
			ADDE(5*(i-1)+j+1,5*(i-1)+j);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=5;j++)
		{
			ADDE(5*(i-1)+j,5*i+j);
		}
	}
	
	
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		e[4*(x-1)+y].f=1;
		e[4*(x-1)+y+4*n].f=1;
	}
	
	int randtimes=10000000/(15*n);
	for(int i=1;i<=randtimes;i++)
	{
		for(int j=1;j<=n;j++) for(int k=1;k<=5;k++) tmpa[j][k]=a[j][k];
		work_rand();
	}
	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
