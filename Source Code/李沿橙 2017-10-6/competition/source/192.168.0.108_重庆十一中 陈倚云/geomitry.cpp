#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn=1e5+7;
int n,q,x,y;
int sx[maxn],sy[maxn];
bool check(int m){
	if(sx[m]*y+x*sy[m]>=sx[m]*sy[m]) return true;
	else return false;
}
int main(){
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&sx[i]);
	for(int i=0;i<n;i++) scanf("%d",&sy[i]);
	sort(sx,sx+n);sort(sy,sy+n);
	scanf("%d",&q);
	while(q--){
		scanf("%d %d",&x,&y);
		int l=0,r=n;
		while(l+1<r){
			int m=(l+r)/2;
			if(check(m)) l=m;
			else r=m;
		}
		if(check(l+1) && l+2<=n) printf("%d\n",l+2);
		else if(check(l) && l+1<=n) printf("%d\n",l+1);
		else if(l==0) printf("0\n"); 
		else if(check(l-1)) printf("%d\n",l);
	}
	
	return 0;
}
