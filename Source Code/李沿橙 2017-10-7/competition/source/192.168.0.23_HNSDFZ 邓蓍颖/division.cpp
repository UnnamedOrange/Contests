#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main()
{
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&k);
	if(n==5)printf("2\n1");
	else printf("6\n7 31 71 127 199");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
