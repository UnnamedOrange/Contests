#include<bits/stdc++.h>
using namespace std;
char a[20005][5005]; 
int lon[20005],use[50];
int n,m,num,x,y;
inline int read()//¶ÁÈëÓÅ»¯
{
  	int num=0;
  	char c;
  	while(isspace(c=getchar()));
  	while(num=num*10+c-48,isdigit(c=getchar()));
  	return num;
}
int cha()
{
	char k;
	bool chek;
	y=read();
	for(int i=1;i<=y;i++)
		use[i]=read();
	for(int i=0;i<=2147483647;i++)
	{
		k=a[use[1]][lon[use[1]]-i];
		for(int j=2;j<=y;j++)
			if(a[use[j]][lon[use[j]]-i]!=k)	{return i;}
	}
}
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	n=read(),m=read();
	for(num=1;num<=n;num++)
		{scanf("%s",a[num]);lon[num]=strlen(a[num])-1;}	
	for(int i=1;i<=m;i++)
	{
		x=read();
		if(x==1)	{scanf("%s",a[num]);lon[num]=strlen(a[num])-1;num++;}
		else
			printf("%d\n",cha());
	}
	return 0;
}
