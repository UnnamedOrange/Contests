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

const int N = 5000000;
const int oo = 0x3f3f3f3f;

template<typename T> T read() {
    T n(0), f(1);
    char ch = getchar();
    for( ;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for( ; isdigit(ch); ch = getchar()) n = n * 10 + ch - 48; 
    return n * f;
}

int n, LIM;
int a[N + 5];
int suf[N + 5], ans;
int dp[N + 5][2], tmp[N + 5][2];

void Input() {
    n = read<int>();

    LIM = 0;
    for(int i = 1; i <= n; ++i) {
        a[i] = read<int>();
        chkmax(LIM, a[i]);
    }
}

void Solve() {
    ans = INT_MAX;
    for(int i = 0; i <= LIM; ++i) dp[i][0] = dp[i][1] = suf[i] = oo;

    dp[0][0] = suf[0] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = a[i-1] + 1; j <= a[i]; ++j) 
            dp[j][0] = dp[j][1] = suf[j] = oo;

        for(int j = a[i]; j >= 0; --j) tmp[j][0] = tmp[j][1] = oo;
        for(int j = a[i]; j >= 0; --j) {
            chkmin(tmp[j][0], suf[a[i] - j] + a[i] - j);
            chkmin(tmp[j][0], dp[a[i] - j][0] + a[i] - j);
            chkmin(tmp[j][1], dp[a[i] - j][0] + a[i] - j);
        }
        suf[a[i] + 1] = oo;
        for(int j = a[i]; j >= 0; --j) {
            dp[j][0] = tmp[j][0];
            dp[j][1] = tmp[j][1];
            suf[j] = min(suf[j + 1], dp[j][1]);
        }
    }
    ans = dp[0][0];
    for(int i = 0; i <= a[n]; ++i) chkmin(ans, dp[i][1]);
    printf("%d\n", ans);
}

int main() {
    freopen("dark.in", "r", stdin);
    freopen("dark.out", "w", stdout);

    Input();
    Solve();

    return 0;
}
