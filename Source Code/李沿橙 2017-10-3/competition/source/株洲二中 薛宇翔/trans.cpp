#include <bits/stdc++.h>
using namespace std;
int read()
{
	int x=0;char c=getchar();
	return (x+c-'0');
}
int n,k;
int num[1000005];
void doit()
{
	for(int i=1;i<n&&k>0;i++)
	{
		if(num[i]==2&&num[i+1]==3)
		{
			if(i%2)num[i+1]=2;
			else num[i]=3,i--;
			k--;
		}
		else continue;
	}
	for(int i=1;i<=n;i++)printf("%d",num[i]);printf("\n");
	return ;
}
int main ()
{	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(scanf("%d%d",&n,&k)!=EOF)
	{	getchar();
		for(int i=1;i<=n;i++)num[i]=read();
		//for(int i=1;i<=n;i++)printf("%d",num[i]);
		doit();
	}
	return 0;
}
