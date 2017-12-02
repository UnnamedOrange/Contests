#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXN 1000005
int n,k;
int a[MAXN];
char x[MAXN];
using namespace std;
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(scanf("%d %d\n",&n,&k)!=EOF)
	{
		for(int i=1;i<=n;i++)
		{
			x[i]=getchar();
			while(x[i]<'0' || x[i]>'9') x[i]=getchar();
			a[i]=x[i]-'0';
		}
		int cnt=0;
		for(int i=1;i<=n-1;)
		{
			if(cnt==k) break;
			if(a[i]==2 && a[i+1]==3 && a[i-1]==2 && i%2==0)
			{
				if((k+cnt)%2==0) break;
				else
				{
					a[i]=3;
					break;
				}
			}
			if(a[i]==2 && a[i+1]==3)
			{
				cnt++;
				if(i%2==1)
				{
					a[i+1]=2;
					i++;
					continue;
				}
				else
				{
					a[i]=3;
					i--;
					continue;
				}
			}
			else i++;
		}
		for(int i=1;i<=n;i++) printf("%d",a[i]);
		printf("\n");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
