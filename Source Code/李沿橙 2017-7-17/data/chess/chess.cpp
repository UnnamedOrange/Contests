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
const int L = 100005;

int n, m;
int row[L], col[L], nr, nc;

void init(void) {
	cin >> n >> m;
}

void work(void) {
	int x, y; LL ans = (LL)n * n;
	rep(i, 1, m) {
		read(x), read(y);
		if(!row[x]) row[x] = 1, ans -= n - nc, nr++;
		if(!col[y]) col[y] = 1, ans -= n - nr, nc++;
		printf("%I64d\n", ans);  
	}
}
int main(int ac, char *av[]) {
  freopen(av[1],"r",stdin), freopen(av[2],"w",stdout);
  init(), work(); return 0;
}


