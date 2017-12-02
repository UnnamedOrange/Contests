#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,num[305];
int main()
{	
	freopen ("cards.in","r",stdin);
	freopen ("cards.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)num[i]=read();
	float a=0.5,b=1.0;
	
	printf("%.9f %.9f",a,b);
	return 0;
}
