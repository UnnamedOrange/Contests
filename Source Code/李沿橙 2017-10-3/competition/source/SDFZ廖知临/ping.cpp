#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;//Map记录二查合并 
int set[100005],n,m,a,b,k,use[100005],Map[100005],up,nax,hao; 
inline int read()//读入优化
{
  	int num=0;
  	char c;
  	while(isspace(c=getchar()));
  	while(num=num*10+c-48,isdigit(c=getchar()));
  	return num;
}
inline int find1(int x)//向上查询并改值 
{
	Map[x]=1;use[x]++;
	while(set[x]!=x)
		{x=set[x];Map[x]=1;use[x]++;}	
	return x;
}
inline int find2(int x)//向上查询并合并
{
	while(set[x]!=x)
		{if(Map[x])	{use[x]++;return x;}//并上以后就返回 
		use[x]++;x=set[x];}	
}
inline int  find3(int x)//向上查询并改值 
{
	Map[x]=0;
	while(set[x]!=x)
		{x=set[x];Map[x]=0;}	
	return 0;
}
inline bool cmp(int a,int b)
{
	if(a>b)	return 1;
	return 0;}
int main()
{
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	set[1]=1;
	n=read();m=read();
    for(int i=1;i<=m;i++)//挂树 
    {	
		a=read();b=read();
		a>b?set[a]=b:set[b]=a;
	}	
	k=read();
	for(int i=1;i<=k;i++)
	{
		a=read();b=read();
		if(a>b)	{find1(b);find2(a);find3(b);}
		else	{find1(a),find2(b),find3(a);}
	}
	for(int i=1;i<=n;i++)
		{if(nax<use[i])	{nax=use[i];hao=i;}}
	sort(use+1,use+n,cmp);
	for(int i=1;i<=n;i++)
		{up+=use[i];if(up>=k)	{printf("%d\n",i);break;}}
	printf("%d",hao);	
	return 0;
}
