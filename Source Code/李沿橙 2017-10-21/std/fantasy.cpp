#include <bits/stdc++.h>
using namespace std;
  
typedef long long LL;
typedef pair<int, int> pii;
  
#define fst first
#define snd second
#define pb push_back
#define REP(i, a, b)  for(int i = (a), i##end = (b); i < i##end; ++i)
#define DREP(i, a, b) for(int i=(a-1), i##end = (b); i >=i##end; --i)
  
template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }
  
const int oo = 0x3f3f3f3f;
const int maxn = 500000 + 10;
 
template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}
 
struct item {
    int v, p, l, r, t;
    bool operator < (const item& rhs) const {
        return v < rhs.v;
    }
}q[maxn << 2];
 
int a[maxn], s[maxn], cnt;
int Mn[maxn][20], Lg[maxn];
 
inline int query(int l, int r) {
    int k = Lg[r - l + 1];
    return s[Mn[l][k]] < s[Mn[r - (1<<k) + 1][k]] ? Mn[l][k] : Mn[r - (1<<k) + 1][k]; 
}
 
int n, k, l, r;
int main() {
    freopen("fantasy.in", "r", stdin);
    freopen("fantasy.out", "w", stdout);
 
    scanf("%d%d%d%d", &n, &k, &l, &r);
    for(int i = 1; i <= n; ++i) s[i] = s[i-1] + (a[i] = read<int>());
    for(int i = 0; i <= n; ++i) Mn[i][0] = i, Lg[i] = (i <= 1) ? 0 : Lg[i>>1] + 1;
 
    for(int j = 1; j < 20; ++j) 
        for(int i = 0; i <= n; ++i) {
            Mn[i][j] = 
                s[Mn[i][j-1]] < s[Mn[i + (1<<(j-1))][j-1]] ? Mn[i][j-1] : Mn[i + (1<<(j-1))][j-1];
        }
 
    for(int i = l; i <= n; ++i) {
        int L = max(0, i - r), R = (i - l), t = query(L, R);
        q[cnt++] = (item) { s[i] - s[t], i, L, R, t };
    }
 
    long long ans = 0;
    make_heap(q, q + cnt);
     
    while(k--) {
        item tmp = q[0]; 
        pop_heap(q, q + (cnt--));
 
        ans += tmp.v;
 
        if(tmp.t > tmp.l) {
            int t = query(tmp.l, tmp.t - 1);
            q[cnt++] = (item) { s[tmp.p] - s[t], tmp.p, tmp.l, tmp.t - 1, t };
            push_heap(q, q + cnt);
        }
 
        if(tmp.t < tmp.r) {
            int t = query(tmp.t + 1, tmp.r);
            q[cnt++] = (item) { s[tmp.p] - s[t], tmp.p, tmp.t + 1, tmp.r, t };
            push_heap(q, q + cnt);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
