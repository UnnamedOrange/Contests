#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;
const int MAXN=1e5+10;
int  h[MAXN],a[MAXN],b[MAXN];
char s[5];
int main()
{
	int i,j,k,l,m,n,p,x,y,tot,pp,qq;
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	
	for (i=1;i<=30000;i++)
	{
		h[i]=1;
		a[i]=i;
		b[i]=1;	
	}	

	scanf("%d",&p);
	while(p--)
	{
		scanf("%s",&s);
		if (s[0]=='C')
		{
			scanf("%d",&x);
			printf("%d\n",h[a[x]]-b[x]);
		}
		if (s[0]=='M')
		{
			scanf("%d%d",&x,&y);
			
			pp=h[a[x]];
			qq=h[a[y]];
			
			h[a[y]]+=h[a[x]];
			h[a[x]]=0;
			
			m=a[y];
			tot=0;
			for (i=1;i<=30000;i++)
			{
				if (a[i]==m)
				{
					b[y]+=pp;
					tot++;
				}
				if (tot==qq)
				{
					break;
				}
			}
			
			m=a[x];
			tot=0;
			for (i=1;i<=30000;i++)
			{
				if (a[i]==m)
				{
					a[i]=a[y];
					tot++;
				}
				if (tot==pp)
				{
					break;
				}
			}			
		}
	}

	fclose(stdin);
	fclose(stdout);

	return 0;
}

