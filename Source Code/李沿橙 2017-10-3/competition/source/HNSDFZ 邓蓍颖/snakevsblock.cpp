#include<bits/stdc++.h>
using namespace std;
struct abc{
	int x,y;
};
int z[210][210],s[210][210],f[8000],things[8000],tot,ans,may[210][210],minn=-9999999/*��С��ǽ*/,maxn=4/*���Ķ�*/,n,m,a[5]={0,0,0,1},b[5]={0,-1,1,0};abc h[40100];//�������ң��£��� 
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
/*δ�����1��һ���������ܱ�һȦǽΧ����������Щǽ���ܽ���ȥ
2��x��������һȦǽ���ȥ���ԳԵ����������һ�������������ȿ��ܼ��٣������ȼ��ٶ����³��Ȳ�����С���Ե����ǽ�ı��������ܷ����÷ֻ�ͣ�
����˵һȦǽΧ��һ��1�Ķ��������г���Ϊ10����С��Χǽ��4��������Ϊ����ֵ����ǽ����Χǽ9��һ��һ�����û���8�����ȱ�Ϊ3��
�����ٴ����κ�Χǽ����ô���ַ�������ֱ��ȥ��Χǽ9.
��3��ÿ��ѡ��С��ǽײ�ǲ�����ģ��ͱ��糤��Ϊ10��Ȼ����һ��Χǽ9��һ��Χǽ4����ȻȥΧǽ9���ţ����ܽ����������ȫ����*/
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
