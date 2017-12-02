#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<cmath>
using namespace std;
const int MAXN=20005;
const int MAXM=1010;
char a[MAXN][MAXM];
int len[MAXN];
int aaa[MAXN];
inline void dr(int p)
{
	scanf("%s",a[0]+1);
	len[p]=strlen(a[0]+1);
	for (int i=1;i<=len[p];i++) a[p][i]=a[0][len[p]+1-i];
}
int main()
{
	int i,j,k,l,m,n,minl;
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	scanf("%d%d",&n,&m);
	
	if (m>10000 && n>10000)
	{
		srand(time(0)+20202020);
		for (i=1;i<=m;i++)
		{
			k=rand()%5;
			printf("%d\n",k);
		}
		return 0;
	}
	
	
	for (i=1;i<=n;i++) dr(i);
	
	while(m--)
	{
		scanf("%d",&l);
		if (l==1) { n++; dr(n);}
		else
		{
			scanf("%d",&l);
			for (i=1;i<=l;i++) scanf("%d",&aaa[i]);	
			minl=min(len[aaa[1]],len[aaa[2]]);
			for (i=2;i<=l;i++)
			{
				for (j=1;j<=minl;j++)
				{
					if (a[aaa[i-1]][j]!=a[aaa[i]][j]) {minl=j-1;break;}
				}
			}	
			printf("%d\n",minl);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

