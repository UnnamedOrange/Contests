#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,m;
int len[3004];
int lcd[3004][3004];
char st[3004][104];
void input()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",&st[i]);
		len[i]=strlen(st[i]);
	}
	return;
}

void found(int x,int y)
{
	int i=len[x]-1,j=len[y]-1;
	int ll=0;
	
	while(i>=0&&j>=0)
	{
		if(st[x][i]!=st[y][j])	break;
		++ll;
		--i;--j;
	}
	
	lcd[x][y]=lcd[y][x]=ll;
	return ;
}

int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	
	input();
	
	for(int i=1;i<=n;++i)
	{
		for(int j=i+1;j<=n;++j)
			found(i,j);
		lcd[i][i]=len[i];
	}
	
	for(int i=1;i<=m;++i)
	{
		int order;
		scanf("%d",&order);	
		
		if(order==1)
		{
			scanf("%s",&st[++n]);
			len[n]=strlen(st[n]);
			for(int j=1;j<n;++j)
				found(n,j);
			lcd[n][n]=len[n];
		}
		
		else
		{
			int nn,cmp[3004];
			int min=0x7fffffff;
			scanf("%d",&nn);
			for(int i=1;i<=nn;++i)
				scanf("%d",&cmp[i]);
			for(int i=1;i<=nn;++i)
				for(int j=i+1;j<=nn;++j)
					if(lcd[cmp[i]][cmp[j]]<min)	{
					min=lcd[cmp[i]][cmp[j]];
					printf("%d,%d %d\n",cmp[i],cmp[j],lcd[cmp[i]][cmp[j]]);
				}
			printf("%d\n",min);
		}
	}
	return 0;
}
/*
5 5
zzj
pri
prime
ime
owaski
2 3 1 3 5
2 2 2 3
1 actri
2 2 3 4
2 3 2 6 5
*/

