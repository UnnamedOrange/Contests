#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;
const int MAXN=310;
int c[1000];
int a[MAXN],now,n;
double ans,q,q1,q2;
bool b[MAXN],b1,b2;
int gcd(int x, int y) {
    if(y==0) return x;
    return gcd(y,x%y);
}
void dfs(int p)
{	
	int nnow;
	if (p>n && p%2==0)
	{
		ans+=1/q2;
		return;
	}
	for (int i=1;i<=n;i++)
	{
		if (b[i])continue;
		b[i]=true;
		nnow=now;
		if (now==0) now=a[i];
		else now=gcd(now,a[i]);
		
		if ((now==1) && (p%2==0))
		{
			if (p==n) q1=1;
			else
			{
				q1=1;
				for (int j=2;j<=n-p;j++)
				{
					q=j;
					q1=q1*q;
				}
			}
			ans+=q1/q2;
			b[i]=false;
			now=nnow;	
			continue;
		}
		if (now==1)
		{
			b[i]=false;
			now=nnow;
			continue;
		} 
		dfs(p+1);
		b[i]=false;
		now=nnow;
	}
	
}
int main()
{
	int k,l,m,cnt,am;
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	//Pro1
	if (n<=15)
	{
		memset(b,false,sizeof(b));
		now=0;
		ans=0;
		m=1;
		for (int i=2;i<=n-1;i++)
		{
			m*=i;
		}
		q2=m;
	
		dfs(1);
		ans/=n;
		printf("%.9f ",ans);
	}
	else
	{
		printf("0.000000000 ");
	}
	//Pro2
	
	for (int i=1;i<=n;i++)
	{
		if (a[i]==1) continue;
		for (int j=1;j<=n;j++)
		{
			if (a[i]==a[j]) continue;
			if (gcd(a[i],a[j])!=1)
			{
				break;
			}
			if (j==n)
			{
				printf("1.000000000");
				return 0;
			} 
		}
	}
	k=0;
	
	am=0;
	for (int i=1;i<=n;i++)
	{
		am=max(a[i],am);		
	}
	for (int i=2;i<am;i++)
	{
		m=sqrt(i);
		b1=true;
		for (int j=2;j<=m;j++)
		if (i%j==0) 
		{
			b1=false;
			break;
		}
		if (b1)
		{
			k++;
			c[k]=i;
		}
	}
	for (int i=1;i<=k;i++)
	{
		//c[k]
		m=0;
		for (int j=1;j<=n;j++)
		{
			if (a[j]%c[i]==0)
			{
				m++;
			}
		}
		if (m&1)
		{
			printf("1.000000000");
			return 0;
		}
	}
	printf("0.000000000");
	fclose(stdin);
	fclose(stdout);
	return 0;
}
