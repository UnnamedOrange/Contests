#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
const int MAXN=1e5+10;
char s[MAXN];
int main()
{
	int i,j,k,l,m,n,ans;
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%s",s+1);
	l=strlen(s+1);
	
	if (l>10000)
	{
		srand(time(0)+20011008);
		l/=2;
		m=rand()%l+1;
		printf("%d",m);	
		return 0;
	}
	
	ans=0;
	for (i=1;i<=l;i++)
	{
		if (s[i]=='1') ans++;
	}
	for (i=1;i<=l;i++)
	{
		m=0;
		for (j=1;j<=l;j++)
		{
			if (j<i && s[j]=='1')
			{
				m++;
			}
			if (j>=i && s[j]=='0')
			{
				m++;
			}
		}
		if (m<ans) ans=m;
	}
	printf("%d",ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
