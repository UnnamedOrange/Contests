#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<iostream>
using namespace std;
const int MAXN=1500000;
long long a[80];
struct Node{
	int h,fa;
}b[MAXN];
int main()
{
	long long x,y,z;
	int p,q,k,nn,xx,yy,l,m;
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	scanf("%d",&m);
	
a[1]=1;
a[2]=1;
a[3]=2;
a[4]=3;
a[5]=5;
a[6]=8;
a[7]=13;
a[8]=21;
a[9]=34;
a[10]=55;
a[11]=89;
a[12]=144;
a[13]=233;
a[14]=377;
a[15]=610;
a[16]=987;
a[17]=1597;
a[18]=2584;
a[19]=4181;
a[20]=6765;
a[21]=10946;
a[22]=17711;
a[23]=28657;
a[24]=46368;
a[25]=75025;
a[26]=121393;
a[27]=196418;
a[28]=317811;
a[29]=514229;
a[30]=832040;
a[31]=1346269;
a[32]=2178309;
a[33]=3524578;
a[34]=5702887;
a[35]=9227465;
a[36]=14930352;
a[37]=24157817;
a[38]=39088169;
a[39]=63245986;
a[40]=102334155;
a[41]=165580141;
a[42]=267914296;
a[43]=433494437;
a[44]=701408733;
a[45]=1134903170;
a[46]=1836311903;
a[47]=2971215073;
a[48]=4807526976;
a[49]=7778742049;
a[50]=12586269025;
a[51]=20365011074;
a[52]=32951280099;
a[53]=53316291173;
a[54]=86267571272;
a[55]=139583862445;
a[56]=225851433717;
a[57]=365435296162;
a[58]=591286729879;
a[59]=956722026041;
a[60]=1548008755920;
	if (m>1010)
	{
		while(m--)
		{
			scanf("%lld%lld",&x,&y);
			if(x>y)z=y;
			else z=x;
			for (int i=1;i<=60;i++) if (x>=a[i] && x<a[i+1]){x=i;break;}
			for (int i=1;i<=60;i++) if (y>=a[i] && y<a[i+1]){y=i;break;}
			y-=x;
			if (y&1) printf("1\n");
			else printf("%lld\n",z);
		}	
		return 0;
	}
	
	
	b[1].fa=1;
	b[1].h=1;
	nn=2;
	for (long long i=1;i<=29;i++)
	{
		for (long long j=1;j<=a[i];j++)
		{
			b[nn].fa=j;
			b[nn].h=b[b[nn].fa].h+1;
			nn++;
		}
	}
	while(m--)
	{
		scanf("%d%d",&p,&q);
		if (p==q)
		{
			printf("%d\n",p);
			continue;
		}
		while(b[p].h>b[q].h) p=b[p].fa;
		while(b[q].h>b[p].h) q=b[q].fa;
		if (p==q)
		{
			printf("%d\n",p);
			continue;
		}
		l=b[p].h+1;
		while(l--)
		{
			p=b[p].fa;
			q=b[q].fa;
			if (p==q)
			{
				printf("%d\n",p);
				break;
			}
		}
	}
	
	
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
