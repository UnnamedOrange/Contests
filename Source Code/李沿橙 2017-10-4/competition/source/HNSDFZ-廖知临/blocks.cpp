#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
int m,n,x,a[5000000],v[5000000];
inline void xuan()
{ 
	int sum=0,sun=0;
	for(int i=1;i<=n;i++)
	{	if(a[i]>x)	sum+=a[i]-x;
		if(a[i]<x)	{sun++;v[sun]=x-a[i];}}	//sum多余数值还有sun个格子v[]格子的需求量
	sort(v+1,v+sun+1);
	int j;
	for(j=1;j<=sun;j++)
	{
		if(sum-v[j]>=0) sum-=v[j];
		else	break;
	}
	printf("%d ",n-sun+j-1);//输出最优 
}
inline int read()//读入优化
{
  	int num=0;
  	char c;
  	while(isspace(c=getchar()));
  	while(num=num*10+c-48,isdigit(c=getchar()));
  	return num;
}
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=m;i++)
	{	
		x=read();
		xuan();
	}	
	return 0;
}
