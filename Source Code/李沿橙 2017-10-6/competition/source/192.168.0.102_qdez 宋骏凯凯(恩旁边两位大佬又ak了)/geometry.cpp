#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
int xx[100001],yy[100001],b[100001];
long double k[100001];
const double eps=1e-10;
bool judge(int now,int x,int y)
{	long double nowy=k[now]*x+(long double)b[now];
	if(nowy<y||fabs(nowy-y)<=eps) return true;
	else return false;
}
int main()
{   freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	int n,x,y,m; scanf("%d",&n);
	for(rint i=1;i<=n;i++) scanf("%d",&xx[i]);
	for(rint i=1;i<=n;i++) scanf("%d",&yy[i]);
	sort(xx+1,xx+n+1); sort(yy+1,yy+n+1);
	for(rint i=1;i<=n;i++) b[i]=yy[i],k[i]=(long double)(-b[i])/xx[i];
	scanf("%d",&m);
	for(rint i=1;i<=m;i++)
	{	scanf("%d%d",&x,&y);
		int l=1,r=n,ans=0;
		while(l<=r)
		{	int mid=(l+r)>>1;
			if(judge(mid,x,y)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}


