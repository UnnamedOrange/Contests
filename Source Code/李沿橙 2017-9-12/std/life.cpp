#include<set>
#include<map>
#include<deque>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<complex>
#include<iostream>
#include<algorithm>
#define ll long long
#define inf 1e9
using namespace std;

inline void read(int &x)
{
	char c;
	while(!((c=getchar())>='0'&&c<='9'));
	x=c-'0';
	while((c=getchar())>='0'&&c<='9') (x*=10)+=c-'0';
}
const int maxn = 1010000;
const int maxk = 21;

int n,K;
int p[maxn],s[maxn];
ll T[maxn];

struct node
{
	int x,i;
	ll y;
	node() {}
	node(const int _x,const ll _y,const int _i)
	{
		x=_x;
		y=_y;
		i=_i;
	}
} q[maxn];
int head,tail;
ll f[maxk][maxn];
int pos[maxk][maxn];
ll multi(node x,node y,node z)
{
	x.x-=z.x;
	x.y-=z.y;
	y.x-=z.x;
	y.y-=z.y;
	return (ll)x.x*y.y-(ll)x.y*y.x;
}
inline bool cmp(const node x,const node y,const ll temp)
{
	return (x.y-y.y)<temp*(ll)(x.x-y.x);
}

int t[maxn],tp;

int main()
{
	freopen("life.in","r",stdin);
	freopen("life.out","w",stdout);

	read(n);
	read(K);
	for(int i=1; i<=n; i++)
	{
		int x,y;
		read(x);
		read(y);
		p[i]=p[i-1]+x;
		s[i+1]=s[i]+y;
		T[i+1]=T[i]+(ll)p[i]*y;
	}
	if(!K)
	{
		printf("%lld\n",T[n+1]);
		puts("");
		return 0;
	}

	f[0][0]=0;
	for(int i=1; i<=n; i++) pos[0][i]=-1;
	for(int k=1; k<=K; k++)
	{
		head=1;
		tail=0;
		for(int i=0; i<=n; i++)
		{
			while(head+1<=tail&&!cmp(q[head],q[head+1],s[i])) head++;
			if(i>=k)
			{
				const int j=q[head].i;
				f[k][i]=f[k-1][j]+T[i]-(ll)(T[j]+(ll)p[j]*(s[i]-s[j]));
				pos[k][i]=j;
			}
			if(i>=k-1&&pos[k-1][i]!=-1)
			{
				const node tmp=node(p[i],f[k-1][i]-T[i]+(ll)p[i]*s[i],i);
				while(head+1<=tail&&multi(q[tail],tmp,q[tail-1])<=0) tail--;
				q[++tail]=tmp;
			}
		}
	}
	int rei;
	ll re=LLONG_MAX;
	for(int i=K; i<=n; i++)
	{
		ll temp=f[K][i]+T[n+1]-(T[i]+(ll)p[i]*(s[n+1]-s[i]));
		if(temp<re) re=temp,rei=i;
	}
	tp=0;
	while(K) t[++tp]=rei,rei=pos[K--][rei];
	printf("%lld\n",re);
	for(int i=tp; i>=2; i--) printf("%d ",t[i]-1);
	printf("%d\n",t[1]-1);

	return 0;
}
