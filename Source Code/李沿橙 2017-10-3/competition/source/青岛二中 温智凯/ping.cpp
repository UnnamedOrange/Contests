#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN];
int main()
{
	int i,j,k,l,m,n;
	freopen("ping.in","r",stdin);
	freopen("ping.out","w",stdout);
	
	srand(time(0)+20202020);
	scanf("%d",&n);
	m=rand()%n+1;
	printf("1\n%d\n",m);

	fclose(stdin);
	fclose(stdout);
	return 0;
}

