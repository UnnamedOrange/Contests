#include<bits/stdc++.h>
#define lol long long
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int m;
lol num[10000];
void doit(lol x,lol y)
{
	lol numx[60],topx=0,numy[60],topy=0;
	memset(numx,0,sizeof(numx));
	memset(numy,0,sizeof(numy));
	numx[0]=x;numy[0]=y;
	for(int i=58;i>=1;i--){
		if(x-num[i]>0){x-=num[i];numx[++topx]=x;}
		if(y-num[i]>0){y-=num[i];numy[++topy]=y;}
	}
	for(int i=topx,j=topy;i>=0,j>=0;i--,j--)
	{	
		if(i==0&&numx[i]==numy[j]){printf("%lld\n",numx[0]);break;}
		if(j==0&&numx[i]==numy[j]){printf("%lld\n",numy[0]);break;}
		if(numx[i]==numy[j])continue;
		if(numx[i]!=numy[j]){
			printf("%lld\n",numx[i+1]);break;
		}
	}
/*	for(int i=0;i<=topx;i++)cout<<numx[i]<<" ";cout<<endl;
	for(int i=0;i<=topy;i++)cout<<numy[i]<<" ";*/
}
int main()
{	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	m=read();
	num[1]=1,num[2]=2;
	for(int i=3;i<=58;i++)
	num[i]=num[i-1]+num[i-2];//,cout<<num[i]<<endl;
	for(int i=1;i<=m;i++)doit(read(),read());
	return 0;
}
