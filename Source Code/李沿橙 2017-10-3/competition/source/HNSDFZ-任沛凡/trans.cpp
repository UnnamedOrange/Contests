#include<cstdio>
using namespace std;
int n,k;
int a[1000010];
char s[1000010];
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		scanf("%s",s+1);
		for(int i=1;i<=n;i++)
		a[i]=s[i]-'0';
		for(int i=1;i<=n;i++)
		{
			if(a[i]==2)
			{
				if(i&1)
				{
					if((a[i+1]==2||a[i+1]==3)&&a[i+2]==3)
					{
						a[i+1]=(a[i+1]-2)^(k&1)+2;
						break;
					}
					else if(a[i+1]==3)
					{
						a[i+1]=2;
						k--;
					}
				}
				else if(a[i+1]==3)
				{
					a[i]=3;
					k--;
				}
			}
		}
		for(int i=1;i<=n;i++)
		printf("%d",a[i]);
		printf("\n");
	}
	return 0;
}
			
			
