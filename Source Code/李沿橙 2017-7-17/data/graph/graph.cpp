#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<ctime>
#include<cmath>
using namespace std;

typedef pair<int, int> Pii;
typedef long long LL;
typedef long double db;
#define rep(_,A,B) for(int _=A;_<=B;++_)
#define per(_,A,B) for(int _=A;_>=B;--_)
#define FOR(_,A) for(int _=h[A];_;_=next[_])
#define fi first
#define se second
#define mp make_pair
#define pb push_back
char o;template<class O> void read(O&x){while(o=getchar(),o<'0'||o>'9');for(x=o^48;o=getchar(),o>='0'&&o<='9';)x=x*10+(o^48);}
const int N = 1e5+5;
int f[N][42],w[N][42];
long long sum[N][42],k,q,s,m;
int main(int ac, char *av[]){
	freopen(av[1], "r", stdin), freopen(av[2], "w", stdout);
	int n,i,j,x,a;
	cin>>n>>k;
	for(i=0;i<n;++i)
		cin>>f[i][0];
	for(i=0;i<n;++i)
		cin>>w[i][0],sum[i][0]= w[i][0];
	for(i=1;i<=40;++i)
		for(j=0;j<n;++j){
			f[j][i]= f[f[j][i-1]][i-1];
			w[j][i]= min(w[j][i-1],w[f[j][i-1]][i-1]);
			sum[j][i]= sum[j][i-1]+ sum[f[j][i-1]][i-1];
		}
	for(i=0;i<n;++i){
		x= i;
		s= w[i][0];m=0;
		for(j=0;j<=41;++j)
			if( k&(1LL<<j)){
				m+= sum[x][j];
				s= min(s,(long long)w[x][j]);
				x= f[x][j];
			}
		printf("%I64d %I64d\n", m, s);
	}
}
