#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
ll mod=1000000007;
ll mod2=mod*mod;
int tp;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=1010000;
const int M=53;

char s[N];
int dp[N][M],pd[N][M],n,id[N];
int val[M][M];
int Q;
ll ai,bi,p,q,r,preans;
int main() {
	scanf("%d%d%lld%d",&n,&Q,&mod,&tp);mod2=mod*mod;
	scanf("%s",s+1);
	rep(i,0,M) rep(j,0,M) val[i][j]=(i==j);
	dp[0][M-1]=pd[0][M-1]=1;
	rep(i,1,n+1) {
		if (s[i]>='a'&&s[i]<='z') id[i]=s[i]-'a'; else id[i]=s[i]-'A'+26;
		rep(j,0,M) {
			val[id[i]][j]=(2*val[M-1][j]-val[id[i]][j]);
			swap(val[id[i]][j],val[M-1][j]);
			if (val[M-1][j]>=mod) val[M-1][j]-=mod;
			if (val[M-1][j]<0) val[M-1][j]+=mod;
			dp[i][j]=val[M-1][j];
		}
	}
	rep(i,0,M) rep(j,0,M) val[i][j]=(i==j);
	rep(i,1,n+1) {
		rep(j,0,M) {
			val[M-1][j]+=val[id[i]][j];
			if (val[M-1][j]>=mod) val[M-1][j]-=mod;
			val[M-1][j]+=val[id[i]][j];
			if (val[M-1][j]>=mod) val[M-1][j]-=mod;
			val[id[i]][j]=-val[id[i]][j];
			if (val[id[i]][j]<0) val[id[i]][j]+=mod;
			swap(val[id[i]][j],val[M-1][j]);
			pd[i][j]=val[M-1][j];
		}
	}
	ll ui,vi,a,b,c;
	if(tp==1)
		scanf("%lld%lld%lld%lld%lld",&ui,&vi,&a,&b,&c);
	const int D=1000000007;
	int xorsum=0;
	rep(i,1,Q+1) {
		int x,y;
		if(tp==1) {
			ll u=(a*ui+b*vi+c*i ^ preans)%D;
			ll v=(b*ui+c*vi+a*i ^ preans)%D;
			ui=u; vi=v;
			x=min(u%n,v%n)+1, y=max(u%n,v%n)+1;
		} else {
			scanf("%d%d",&x,&y);
		}
		preans=0;
		rep(j,0,M) {
			preans=(preans+(ll)dp[y][j]*pd[x-1][j]);
			if (preans>=mod2) preans-=mod2;
		}
		preans%=mod;
		(preans+=mod-1)%=mod;
		//cout<<x<<' '<<y<<endl;
		xorsum^=preans;
		//if(tp==0)printf("%lld\n",preans);
	}
	if(tp==1)printf("%lld\n",preans);
	else printf("%d\n",xorsum);
}