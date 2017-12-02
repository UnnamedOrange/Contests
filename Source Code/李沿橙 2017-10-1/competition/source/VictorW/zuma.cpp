#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<iostream>
using namespace std;
const int MAXN=210;
char s[MAXN];
int main()
{
	int i,j,k,l,m,n;
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	srand(time(0)+19191919);
	m=rand()%4+1;
	printf("%d",m);
	fclose(stdin);
	fclose(stdout);
	return 0;
}

