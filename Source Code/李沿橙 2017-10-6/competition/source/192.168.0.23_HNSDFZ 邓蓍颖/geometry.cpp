#include<bits/stdc++.h>
using namespace std;
int n,m;
int pointx[101000],pointy[101000],ans,addx,addy;double text[101000];
int read()
{
	char c;
	c=getchar();
	while(c>'9'||c<'0')
		c=getchar();
	return c-'0';
}
void search(int l,int r)//尝试二分？ 
{
	int mid=(l+r)/2;
	if((double)(addy)>=(double)(pointy[mid]-addx*text[mid])&&(double)(addy)<(double)(pointy[mid+1]-addx*text[mid+1]))printf("%d\n",mid);
	if(r>l&&(double)(addy)>=(double)(pointy[mid]-addx*text[mid]))search(mid+1,r);//因为mid会向左偏，所以取右边的时候要加1 
	else if(r>l)search(l,mid);
}
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)pointx[i]=read();//读入原本的点
	for(i=1;i<=n;i++)pointy[i]=read();
	sort(pointx+1,pointx+n+1);
	sort(pointy+1,pointy+n+1);
	for(i=1;i<=n;i++)text[i]=double(pointy[i]/pointx[i]);
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{	
		addx=read(),addy=read();//读入要查询的点
		//scanf("%d%d",&addx,&addy);
		if((double)(addy)>=(double)(pointy[n]-addx*text[n]))printf("%d\n",n);
		else	if((double)(addy)<(double)(pointy[1]-addx*text[1]))printf("0\n");
		else search(1,n-1);//在ans的右边插入，也就是说要大于等于ans位置的线段，小于ans+1位置的线段 
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
