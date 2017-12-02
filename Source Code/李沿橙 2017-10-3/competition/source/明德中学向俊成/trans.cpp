#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
int a[100010];
char c;
using namespace std;
int main()
{
	freopen("trans.in","r",stdin);freopen("trans.out","w",stdout);
	int i,j,k,m,n,t;
	while(scanf("%d%d\n",&n,&k)!=EOF) 
	{
		for(i=1;i<=n;i++)
		{
			scanf("%c",&c);
			a[i]=c-'0';
		}
		t=0;
		for(j=1;j<n;j++)
		{
			if(a[j]==2&&a[j+1]==3)
			{
				if(j%2==0)
				{
					a[j]=3;
					if(a[j-1]==2)
					{
						if(k%2==0)
						{
							a[j]=2;
							break;
						}
						else
						{
							break;
						}
					}
					t++;
					if(t==k)
					{
						break;
					}
				}
				else if(j%2==1)
				{
					a[j+1]=2;
					if(a[j+2]==3)
					{
						if(k%2==0)
						{
							a[j+1]=3;
							break;
						}
						else
						{
							break;
						}
					}
					t++;
					if(t==k)
					{
						break;
					}
				}
			}
		}
		for(i=1;i<=n;i++)
		{
			printf("%d",a[i]);
		}
		printf("\n");
	}
	return 0;
}
