#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int b[30001],c[30001],d[30001];//  b是记录每个栈有多少个数，c是记录每个方块下有多少个方块 
int main()
{
freopen("cube.in","r",stdin);
freopen("cube.out","w",stdout);
	memset(c,0,sizeof(c));
	int n,g1,g2,k,r;
	char s;
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{d[i]=i;b[i]=1;c[i]=0;}
	for(int i=1;i<=n;i++)
	{
	cin>>s;
	if (s=='M') 
	{
	scanf("%d%d",&g1,&g2);
	int h=d[g1],h1;
		  

    for(int z=1;z<=n;z++)
	{
		if (d[z]==h) c[z]+=b[g2];
    }
    	    for(int z=1;z<=n;z++)
	{
      if (d[z]==h)  d[z]=g2;
    }
	b[g2]+=b[h];
		
		b[h]=0;

	
     
	}
	if (s=='C') {scanf("%d",&g1);cout<<c[g1]<<endl;}
	}
return 0;

}

