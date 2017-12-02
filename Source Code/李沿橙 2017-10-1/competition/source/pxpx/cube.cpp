#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
using namespace std;
int p,a,b;
char s;

struct px
{
   int c;
	int d;
	int h;
	int t;
}x[30000+50];

inline int ddied(int t)
{
	if(x[t].h!=t)
	x[t].h=dide(x[t].h);
	return x[t].h;
}

inline int died(int t)
{
	if(x[t].t!=t)
	x[t].t=dide(x[t].t);
	return x[t].t;
}

inline int find(int t)
{
	
}

int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	for(int i=1;i<=30000+50;i++)
	x[i].h=x[i].t=i;
	scanf("%d",&p);
	for(int i=1;i<=p;i++)
	{
		scanf("%c",&s);
		if(s=='M')
		{
			scanf("%d%d",&a,&b);
			int j,k;
			j=dide(a);
			k=ddide(b);
			x[j].t=k;
			x[k].h=j;
		}
		else
		{
			scanf("%d",&a);
			int ans;
			ans=find(a);
			printf("%d\n",ans);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
