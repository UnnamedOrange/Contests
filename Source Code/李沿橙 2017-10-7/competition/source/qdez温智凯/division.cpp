#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<iostream>
using namespace std;
const int MAXN=140000;
int a[MAXN],b[MAXN];
int main()
{
	int k,l,r,m,n,ans;
	bool b1;
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);

	scanf("%d%d",&n,&k);
	if (k==1)
	{
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		l=1;
		r=2;
		ans=1;
		while(r<=n)
		{
			for (int i=l;i<=r-1;i++)
			{
				m=sqrt(a[i]+a[r]);
				m*=m;
				if (m==(a[i]+a[r]))
				{
					l=r;
					r++;
					b[ans]=l-1;
					ans++;
				}	
			}
			r++;	
		}
		printf("%d\n",ans);
		if (ans==1)
		{
			printf("\n");
			return 0;
		}
		for (int i=1;i<=ans-1;i++)
		{
			printf("%d ",b[i]);
		}
		return 0;
	}
	
	if (n==2)
	{
		scanf("%d%d",&a[1],&a[2]);
		m=sqrt(a[1]+a[2]);
		m*=m;
		if (m==(a[1]+a[2]))
		{
			printf("2\n1");
		}
		else
		{
			printf("1\n\n");
		}
		return 0;
	}
	
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	
	b1=true;
	for (int i=1;i<=n-1;i++)
	{
		if (b1)
		{
			for (int j=i+1;j<=n;j++)
			{
				m=sqrt(a[i]+a[j]);
				m*m;
				if (m!=(a[i]+a[j]))
				{
					b1=false;
					break;
				}
			}
		}
	}
	if (!b1)
	{
		printf("1\n\n");
		return 0;
	}
	
	l=1;
	r=2;
	ans=1;
	while(r<=n)
	{
		for (int i=l;i<=r-1;i++)
		{
			m=sqrt(a[i]+a[r]);
			m*=m;
			if (m==(a[i]+a[r]))
			{
				l=r;
				r++;
				b[ans]=l-1;
				ans++;
			}	
		}
		r++;	
	}
	if (ans&1) printf("%d",(ans+1)/2);
	else printf("%d",ans/2);
	
	//printf("%d\n",ans);
	if (ans==1 || ans==2)
	{
		printf("\n");
		return 0;
	}
	
	for (int i=1;i<=ans-1;i+=2)
	{
		printf("%d ",b[i]);
	}
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}

