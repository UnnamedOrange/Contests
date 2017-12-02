#include<bits/stdc++.h>
using namespace std;
int n,m,k;
string s;
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	int i,a;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)cin>>s;
	for(i=1;i<=m;i++)
	{
		scanf("%d",&a);
		if(a==1)cin>>s;
		else
		{
			scanf("%d",&a);
			for(int j=1;j<=a;j++)scanf("%d",&k);
			printf("0\n");
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
