#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;
int n,m;
int x[maxn],y[maxn];
int main(){
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&x[i]);
	for(int i=1;i<=n;i++) scanf("%d",&y[i]);
	sort(x+1,x+n+1),sort(y+1,y+n+1);
	int a,b,l,r,mid;
	scanf("%d",&m);
	while(m--){
		scanf("%d%d",&a,&b);
		l=0,r=n;
		while(l<r){
			mid=l+r>>1;
			if(b<-1.0*y[mid]/x[mid]*a+y[mid]) r=mid-1;
			else l=mid+1;
		}
		if(b<-1.0*y[r]/x[r]*a+y[r]) r--;
		printf("%d\n",r);
	}
	return 0;
} 
