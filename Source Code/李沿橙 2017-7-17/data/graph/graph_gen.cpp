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

int n = 100000;
LL k = 1e10;

int R(int x) {
	return rand() % x;
}

void init(void) {
	srand(time(0));
	cout << n << " " << k << endl;
	rep(i, 1, n) printf("%d%c", R(n), i != n ? ' ' : '\n');
	rep(i, 1, n) printf("%d%c", R((int)1e8), i != n ? ' ' : '\n');
}

void work(void) {
}
int main(void) {
  freopen("graph10.in","w",stdout);
  init(), work(); return 0;
}


