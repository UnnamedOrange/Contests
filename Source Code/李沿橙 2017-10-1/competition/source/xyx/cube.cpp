#include <bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,num[30005][2];
int find(int x)
{
	int ax=x;int ay;
	while(num[ax][0]){
		ax=num[ax][0];
		}
	/*ay=num[ax][1];
	while(ay&&num[ay][1]!=x){
		num[num[ay][1]][0]=ax;
		ay=num[ay][1];
	}
	num[x][0]=ax;*/
	return ax; 
}
int findd(int y)
{
	int bx=y;int by;
	while(num[bx][1]){
		bx=num[bx][1];
	}
	/*by=num[bx][0];
	while(by&&num[by][0]!=y){
		num[num[by][0]][1]=bx;
		by=num[by][0];
	}
	num[y][1]=bx;*/
	return bx;
}
int ans(int ss)
{
	int aaa,p=0;
	while(num[ss][0]){
		p++;
		aaa=num[ss][0];
		ss=aaa;
	}
	return p;
}
int main()
{	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		char a;int b,c;
		scanf("%c",&a);
		b=read();
		if(a=='M')c=read();
		if(a=='M'){
			int aa=findd(c),bb=find(b);
			num[bb][0]=aa;
			num[aa][1]=bb;
			continue;}
		if(a=='C'){printf("%d\n",ans(b));continue;}
	}
	
	return 0;
}
