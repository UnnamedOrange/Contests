#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
char a[1000001];
int main()
{   freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	int n,k;
	while(~scanf("%d%d",&n,&k))
	{	scanf("%s",a+1); int p=0;
		for(rint i=1;i<=n;i++)
		{	if(a[i]=='3'&&a[i-1]=='2')
			{	if((i-1)&1) a[i]='2';
				else
				{	a[i-1]='3';
					if(a[i-2]=='2') a[i-1]='2';
				}
				p++;
			}
			if(p==k) break;
		}
		for(rint i=1;i<=n;i++) printf("%c",a[i]);
		printf("\n");
	} 
	return 0;
}



