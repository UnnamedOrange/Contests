#include<cstdio>
using namespace std;
long long b[1400000],c[60],Map[1400000];
int m;//b指祖先 
inline int read()
{
	int x=0;
	char c;
	c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
inline int find1(int x)//向上查询并改值 
{
	Map[x]=1;
	while(b[x]!=x)
		{x=b[x];Map[x]=1;}	
	return 0;
}
inline int find2(int y)//向上查询并对接找祖先 
{
	if(Map[y]==1)	return y;
	while(b[y]!=y)
		{y=b[y];if(Map[y]==1)	return y;}	
}
inline int find3(int x)//向上查询并删除值 
{
	Map[x]=0;
	while(b[x]!=x)
		{x=b[x];Map[x]=0;}	
	return 0;
}
int zuo()//解决1346269以内的数据 
{
	int  num=3;
	b[1]=1,b[2]=1;
	for(int i=1;i<=30;i++)
	{
		for(long long j=1;j<=c[i];j++)
			b[num++]=j;
	}
	int x,y;
	for(int i=1;i<=m;i++)	
	{
		x=read();y=read();
		if(x>y)	{find1(y);printf("%d\n",find2(x));find3(y);}
		else	{
		if(x==y)	printf("%d\n",x);
		else	{find1(x);printf("%d\n",find2(y));find3(x);}}
	}
}
int shu()
{
	c[0]=1;c[1]=1;
	for(int i=2;i<=60;i++)//60个就到了10的13次方了 
		c[i]=c[i-1]+c[i-2];
} 
int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
    scanf("%d",&m);
    if(m>300000)
	{
		shu();long long x,y;
		for(int z=1;z<=m;z++)	
		{
			x=read();y=read();
			if(x>y)
			{
				int i,j;
				for(i=1;i<=60;i++)
					if(c[i]==x)	break;
				for(j=i;j>=1;j-=2)
					if(c[j]==y)	break;
				if(j==1)	printf("1\n");
				else	printf("%lld\n",c[j]);
			}
			else	{
			if(x==y)	printf("%lld\n",x);
			else	{
			int i,j;
			for(i=1;i<=60;i++)
				if(c[i]==y)	break;
			for(j=i;j>=1;j-=2)
				if(c[j]==x)	break;
			if(j==1)	printf("1\n");
			else	printf("%lld\n",c[j]);}}
		}
	}
	else{shu();zuo();}
    return 0;
}
