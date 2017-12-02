#include<algorithm>
#include<cstdio>
using namespace std;
long long k,n,m,q,a[200005],b[200005];
long long c[200005];
void read(long long &n)
{
   	long long x=0;
    	char ch=getchar();
    	while (ch<'0' || ch>'9') ch=getchar();
    	while (ch<='9' && ch>='0') x=(x<<1)+(x<<3)+ch-48,ch=getchar();
    	n=x;
}
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	read(n),read(m),read(k);
	for (int i=1;i<=n;i++) read(a[i]);
	for (int i=1;i<=m;i++) read(b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	long long l=a[1]*b[1],r=a[n]*b[m],mid,p;
	while (l<=r)
	{
		mid=(l+r)>>1;
		p=0;
		q=m;
		for (int i=1;i<=n;i++) 
		{
			while (a[i]*b[q]>mid && q) q--;
			p+=q;
		}
		if (p==k) break;
		if (p<k) l=mid+1; else r=mid-1;
	}
	if (l>r) mid=l;
	q=m;
	for (int i=1;i<=n;i++) 
	{
		while (a[i]*b[q]>mid && q) q--;
		c[i]=a[i]*b[q];
	}
	sort(c+1,c+n+1);
	printf("%lld",c[n]);
	return 0;
}
