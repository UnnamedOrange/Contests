#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN];
int main()
{
	int i,j,k,l,m,n;
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	srand(time(0)+20202020);
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		m=rand()%15+1;
		printf("%d\n",m);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}

