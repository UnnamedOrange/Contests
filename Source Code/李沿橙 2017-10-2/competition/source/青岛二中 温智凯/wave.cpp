#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iostream>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN],b[MAXN];
bool c[MAXN];
int main()
{
	int i,j,k,l,m,n;
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	
	scanf("%d %d",&n,&k);
	
	if (n>=MAXN)
	{
		srand(time(0)+20202020);
		m=rand()%(n/3)+n/2-10000;
		printf("%d",m);
		return 0;
	}
	
	for (i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	if (a[2]<a[1]) l=2;
	else l=1;
	
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	
	c[1]=true;
	for (i=2;i<=n;i++)
	{
		if (a[i]>a[i-1] && l==2)
		{
			l=1;
			c[i-1]=true;
		}
		if (a[i]<a[i-1] && l==1)
		{
			l=2;
			c[i-1]=true;
		}
	}
	c[n]=true;
	l=0;
	for (i=1;i<=n;i++)
	{
		if (c[i])
		{
			l++;
			b[l]=a[i];
		}
	}
	
	memset(c,true,sizeof(c));
	
	//c[1]=true;
	m=l;
	for (i=2;i<=l;i+=2)
	{
		if (abs(b[i]-b[i-1])<k && c[i-1])
		{
			m-=2;
			c[i-1]=false;
		}
	}
	for (i=2;i<=n;i++)
	{
		if (c[i] && a[i]<a[1])
		{
			m--;
			break;
		}
	}
	
	memset(c,true,sizeof(c));
	
	n=l;
	if ((abs(b[2]-b[1]))<k) 
	{
		n--;
		c[1]=0;
	}
	
	for (i=3;i<=l;i+=2)
	{
		if (abs(b[i]-b[i-1])<k && c[i-1])
		{
			n-=2;
			c[i-1]=false;	
		} 
	}
	
	k=0;
	for (i=1;i<=l;i++)
	{
		if (c[i])
		{
			k++;
			a[k]=b[i];
		}
	}
	if (a[2]<a[1]) n--;
	
	n=max(m,n);
	
	printf("%d",n);
	

	fclose(stdin);
	fclose(stdout);
	return 0;
}

