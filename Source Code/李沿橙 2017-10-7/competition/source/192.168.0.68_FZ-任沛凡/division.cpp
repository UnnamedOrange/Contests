#include<cmath>
#include<cstdio>
#include<algorithm>
#define maxn 200010
using namespace std;
int a[maxn],b[maxn],num[maxn];
int v[maxn],v1[maxn],v2[maxn];
int n,k,cnt,c1,c2;
bool flag;
bool cmp(int x,int y)
{
	return v[x]>v[y];
}
bool judge(int x)
{
	int t=sqrt(x);
	return t*t==x;
}
bool check(int l,int r)
{
	c1=0,c2=0;
	for(int i=l;i<=r;i++)
	v[i]=0;
	for(int i=l;i<=r;i++)
	for(int j=i+1;j<=r;j++)
	{
		if(judge(a[i]+a[j]))
		v[i]++,v[j]++;
	}
	for(int i=l;i<=r;i++)
	b[i]=i;
	sort(b+l,b+r+1,cmp);
	v1[++c1]=a[b[l]];
	for(int i=l+1;i<=r;i++)
	{
		flag=0;
		for(int j=1;j<=c1;j++)
		{
			if(judge(v1[j]+a[b[i]]))
			{
				if(c2==0)
				v2[++c2]=a[b[i]];
				else
				{
					for(int k=1;k<=c2;k++)
					if(judge(v2[k]+a[b[i]]))
					return 0;
					v2[++c2]=a[b[i]];
				}
				flag=1;
				break;
			}
		}
		if(!flag)
		v1[++c1]=a[b[i]];
	}
	return 1;
}
int main()
{
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	int x,l,r,mid,ans;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	check(2,n);
	x=n;
	if(k==1)
	for(int i=n-1;i;i--)
	{
		for(int j=i+1;j<=x;j++)
		if(judge(a[i]+a[j]))
		{
			x=i;
			num[++cnt]=x;
		}
	}
	else
	while(1)
	{
		l=1;
		r=x;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(check(mid,x))
			{
				ans=mid;
				r=mid-1;
			}
			else
			l=mid+1;
		}
		x=ans-1;
		if(x==0)
		break;
		num[++cnt]=x;
	}
	cnt++;
	printf("%d\n",cnt);
	for(int i=cnt-1;i;i--)
	printf("%d ",num[i]);
	printf("\n");
	return 0;
}
