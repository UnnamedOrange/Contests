#include<cstdio>
#include<vector>
using namespace std;
const int maxn=3e5+10;
inline int swap(int&x,int&y){x^=y,y^=x,x^=y;}
int n,m;
int s[maxn],p[maxn],q[maxn];
vector<int>v[maxn];
int main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&q[i]);
		if(!s[q[i]]) v[q[i]].push_back(0),s[q[i]]++;
		v[q[i]].push_back(i);
		p[i]=s[q[i]];
		s[q[i]]++;
	}
	int a,b,c,d,l,r,mid;
	while(m--){
		scanf("%d",&a);
		if(a==1){
			scanf("%d%d%d",&b,&c,&d);
			l=0,r=s[d]-1;
			while(l<r){
				mid=l+r>>1;
				if(v[d][mid]>=b) r=mid-1;
				else l=mid+1;
			}
			if(v[d][r]>=b) r--;
			b=r,l=0,r=s[d]-1;
			while(l<r){
				mid=l+r>>1;
				if(v[d][mid]>c) r=mid-1;
				else l=mid+1;
			}
			if(v[d][r]>c) r--;
			printf("%d\n",r-b);
		}
		else{
			scanf("%d",&b);
			c=q[b],d=q[b+1];
			if(c==d) continue;
			v[c][p[b]]=b+1;
			v[d][p[b+1]]=b;
			swap(p[b],p[b+1]);
			swap(q[b],q[b+1]);
		}
	}
	return 0;
}
