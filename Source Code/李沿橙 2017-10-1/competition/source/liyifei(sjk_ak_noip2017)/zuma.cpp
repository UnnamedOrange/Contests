#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char a[305];
int f[205][205][3][3];
int main()
{
	int b,bb,c,cc,d,dd,e,ee,tmp;
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	int i,j,k,l,x,y,n,t;
	scanf("%s",a+1);
	n=strlen(a+1);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			for(k=0;k<=2;k++)
				for(l=0;l<=2;l++)
					f[i][j][k][l]=10007;
	for(i=1;i<=n;i++)
	{
		if(a[i]!=a[i-1]&&a[i]!=a[i+1])
		{
			f[i][i][0][0]=2;
			if(a[i]=='0')
				f[i][i][1][0]=0;
			else
				f[i][i][0][1]=0;
		}
	}
	for(j=1;j<=n;j++)
	{
		for(i=1;i+j<=n;i++)
		{
			t=i+j;
			if(j==1&&a[i]==a[t])
			{
				f[i][t][0][0]=1;
				if(a[i]=='0')
					f[i][t][2][0]=0;
				else
					f[i][t][0][2]=0;
				continue;
			}
			if(a[i]==a[i-1]||a[t]==a[t+1])
				continue;
			for(k=i;k<t;k++)
			{
				if(a[k]==a[k+1])
					continue;
				for(l=0;l<=2;l++)
					for(x=0;x<=2;x++)
						for(y=0;y<=2;y++)
						{	
							tmp=min(min(f[i][k][x][0]+f[k+1][t][y][0]+max(3-x-y,0)+l,f[i][k][x][0]+f[k+1][t][0][y]+(3-x)%3+(l-y+3)%3),min(f[i][k][0][x]+f[k+1][t][y][0]+(3-y)%3+(l-x+3)%3,f[i][k][0][x]+f[k+1][t][0][y]+(l-(3-max(3-x-y,0))+3)%3));	
							f[i][t][0][l]=min(f[i][t][0][l],tmp);
						if(l!=0)
						{tmp=min(min(f[i][k][x][0]+f[k+1][t][y][0]+(l-(3-max(3-x-y,0))+3)%3,f[i][k][x][0]+f[k+1][t][0][y]+(3-y)%3+(l-x+3)%3),min(f[i][k][0][x]+f[k+1][t][y][0]+(3-x)%3+(l-y+3)%3,f[i][k][0][x]+f[k+1][t][0][y]+max(3-x-y,0)+l));
						f[i][t][l][0]=min(f[i][t][l][0],tmp);
						}
						
	//f[i][i+j][0][l]=min(f[i][i+j][0][l],f[i][k][x][0]+f[k+1][i+j][y][0]+max(3-x-y,0)+l);//x0y0
	//f[i][i+j][0][l]=min(f[i][i+j][0][l],f[i][k][x][0]+f[k+1][i+j][0][y]+(3-x)%3+(l-y+3)%3);//x00y
	//f[i][i+j][0][l]=min(f[i][i+j][0][l],f[i][k][0][x]+f[k+1][i+j][y][0]+(3-y)%3+(l-x+3)%3);//0xy0
	//f[i][i+j][0][l]=min(f[i][i+j][0][l],f[i][k][0][x]+f[k+1][i+j][0][y]+(l-(3-max(3-x-y,0))+3)%3);//0x0y
	//f[i][i+j][l][0]=min(f[i][i+j][l][0],f[i][k][x][0]+f[k+1][i+j][y][0]+(l-(3-max(3-x-y,0))+3)%3);//x0y0
	//f[i][i+j][l][0]=min(f[i][i+j][l][0],f[i][k][x][0]+f[k+1][i+j][0][y]+(3-y)%3+(l-x+3)%3);//x00y
	//f[i][i+j][l][0]=min(f[i][i+j][l][0],f[i][k][0][x]+f[k+1][i+j][y][0]+(3-x)%3+(l-y+3)%3);//0xy0
	//f[i][i+j][l][0]=min(f[i][i+j][l][0],f[i][k][0][x]+f[k+1][i+j][0][y]+max(3-x-y,0)+l);//0x0y
						}
			}
			//printf("%d ",f[1][1][0][1]);
			//printf("%d %d %d\n",i,t,f[i][t][0][0]);
		}
	}
	printf("%d",f[1][n][0][0]);
	return 0;
}
//printf("%d ",f[1][4][0][0]);
//printf("%d %d",f[1][2][1][0],f[3][4][2][0]);
/*

*/
//							b=f[i][k][x][0]+f[k+1][t][y][0]+max(3-x-y,0)+l;
//							c=f[i][k][x][0]+f[k+1][t][0][y]+(3-x)%3+(l-y+3)%3;
//							d=f[i][k][0][x]+f[k+1][t][y][0]+(3-y)%3+(l-x+3)%3;
//							e=f[i][k][0][x]+f[k+1][t][0][y]+(l-(3-max(3-x-y,0))+3)%3;
//							bb=f[i][k][x][0]+f[k+1][t][y][0]+(l-(3-max(3-x-y,0))+3)%3;
//							cc=f[i][k][x][0]+f[k+1][t][0][y]+(3-y)%3+(l-x+3)%3;
//							dd=f[i][k][0][x]+f[k+1][t][y][0]+(3-x)%3+(l-y+3)%3;
//							ee=f[i][k][0][x]+f[k+1][t][0][y]+max(3-x-y,0)+l;
//							f[i][t][0][l]=min(min(b,c),min(d,e));
//							f[i][t][l][0]=min(min(bb,cc),min(dd,ee));

