#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>

using namespace std;
const int len=1000000+50;
int n,m,a;
int x[len],y[500],z[len];

int jk(int t)
{
	int ans=0,j=0,sum=0,mark=0;
	for(int i=1;i<=n;i++)
	{
		if(x[i]>=t&&!mark)
		{
			j=i-1;
			mark++;
			ans++;
			sum+=x[i]-t;
			continue;
		}
		if(mark&&i==n)
		{
			if(sum+x[i]>=t)
			{
				ans++;
				sum+=x[i]-t;
			}
			if(j)
			{
				if(sum+x[j]>=t)
					{
						ans++;
						sum+=x[j]-t;
						j--;
					}
			}
			break;
		}
		if(mark)
		{
			if(sum+x[i]>=t)
			{
				ans++;
				sum+=x[i]-t;
			}
			else
			{
				if(j)
				{
					if(sum+x[j]>=t)
					{
						ans++;
						sum+=x[j]-t;
						j--;
					}
					else
					break;
				}
			}
		}
	}
	return ans;
}

int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%d",&x[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a);
		y[i]=jk(a);
	}
	for(int i=1;i<=m;i++)
	printf("%d ",y[i]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
