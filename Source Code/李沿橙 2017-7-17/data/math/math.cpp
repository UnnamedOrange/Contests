#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<ctime>
using namespace std;

typedef long long LL;
#define rep(_,A,B) for(int _=A;_<=B;++_)
#define per(_,A,B) for(int _=A;_>=B;--_)

int k, p;
LL mod;

LL mult(LL x, LL y) {
     LL t = 0;
     for(; y; y >>= 1, x = (x + x) % mod) if(y & 1ll) t = (t + x) % mod;
     return t;
}

void init(void) {
     cin >> k >> p;
}

void work(void) {
     mod = (LL)p * p;
     LL t;
     if(p == 2) t = 5;
     else t = (LL)p * (p + 1) / 2;
     LL t1 = mult(k, t);
     LL t2 = mult(mult((LL)p * (p - 1), 2 * p - 1), (LL)(k - 1) * k / 2);
     LL ans = (t1 + t2) % mod;
     cout << ans << endl;
}
int main(int ac, char *av[]) {
  freopen(av[1],"r",stdin), freopen(av[2],"w",stdout);
  init(), work(); return 0;
}
