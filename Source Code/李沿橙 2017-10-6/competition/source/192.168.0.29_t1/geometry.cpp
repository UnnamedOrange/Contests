#include<algorithm>
#include<iostream>
#include<cstdio>

using namespace std;
const int N=100005;
long long a,b;
long long x[N],y[N];
bool check(int i)
{
	if((x[i]-a)*y[i]>b*x[i]) return 1;
	return 0;
}
int main()
{	
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	long long n,m;	
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&x[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&y[i]);
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	scanf("%lld",&m);
	int l,r,mid;
	for(int i=1;i<=m;i++)
	{
		l=1,r=n;
		scanf("%lld%lld",&a,&b);
		while(l<=r) {
			mid=(l+r)/2;
			if((x[mid]-a)*y[mid]==b*x[mid]) 
		   	{
				l=-1;
				printf("%d\n",mid);
				break;
			}
			else 
				if(check(mid)) r=mid-1;
				else l=mid+1; 		
		}
		if(l>=0) printf("%d\n",l-1);
	}
	fclose(stdin);
	fclose(stdout);	
	return 0;
}
