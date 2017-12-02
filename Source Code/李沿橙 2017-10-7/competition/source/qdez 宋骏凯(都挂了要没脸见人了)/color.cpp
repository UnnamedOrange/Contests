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
vector<int> a[300010];
int pos[300010];
int main()
{   freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int n,m,l,r,k,x; scanf("%d%d",&n,&m);
	for(rint i=1;i<=n;i++) scanf("%d",&pos[i]),a[pos[i]].push_back(i);
	for(rint i=1;i<=300000;i++) sort(a[i].begin(),a[i].end());
	for(rint i=1;i<=m;i++)
	{	int opt; scanf("%d",&opt);
		if(opt==1)
		{	scanf("%d%d%d",&l,&r,&k);
			int ll=0,rr=a[k].size()-1,ans=-1;
			while(ll<=rr)
			{	int mid=(ll+rr)>>1;
				if(a[k][mid]>=l) ans=mid,rr=mid-1;
				else ll=mid+1;
			}
			if(ans==-1) {printf("0\n");continue;}
			ll=0,rr=a[k].size()-1; int an=-1;
			while(ll<=rr)
			{	int mid=(ll+rr)>>1;
				if(a[k][mid]<=r) an=mid,ll=mid+1;
				else rr=mid-1;
			}
			if(an==-1) {printf("0\n");continue;}
			else printf("%d\n",an-ans+1);
		}
		else
		{	scanf("%d",&x);
			if(pos[x]==pos[x+1]) continue;
			else
			{	a[pos[x]][lower_bound(a[pos[x]].begin(),a[pos[x]].end(),x)-a[pos[x]].begin()]++;
				a[pos[x+1]][lower_bound(a[pos[x+1]].begin(),a[pos[x+1]].end(),x+1)-a[pos[x+1]].begin()]--;
				swap(pos[x],pos[x+1]);
			}	
		}
	}
 	return 0;
}



