#include <bits/stdc++.h>

using namespace std;

#define rep(i, l, r) for(int i = l, i##end = r; i <= i##end; ++i)
#define drep(i, l, r) for(int i = l, i##end = r; i >= i##end; --i)
#define erep(i, u) for(int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])
#define ms(a, b) memset(a, b, sizeof a)

template<class T> inline bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template<class T> inline bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

template<typename T> inline T& read(T& x)
{
	static char c; bool flag = 0;
	while (!isdigit(c = getchar())) if (c == '-') flag = 1;
	for (x = c - '0'; isdigit(c = getchar()); (x *= 10) += c - '0');
	if (flag) x = -x;
	return x;
}

const int maxn = 1010, maxm = maxn * maxn;

int n, ans, dp[maxn];

struct data
{
	int x, y, z;

	bool operator < (const data& rhs) const { return x < rhs.x; }
} p[maxn];

int head[maxn], nxt[maxm], to[maxm], e;
void ae(int x, int y) { to[++e] = y; nxt[e] = head[x]; head[x] = e; }

bool vis[maxn];
int linkx[maxn];

bool dfs(int u)
{
	erep(i, u) if (!vis[v])
	{
		vis[v] = 1;
		if (!linkx[v] || dfs(linkx[v])) { linkx[v] = u; return 1; }
	}
	return 0;
}

int main()
{
	freopen("missile.in", "r", stdin);
	freopen("missile.out", "w", stdout);
	read(n);
	rep(i, 1, n) read(p[i].x), read(p[i].y), read(p[i].z);
	sort(p + 1, p + n + 1);
	rep(i, 1, n)
	{
		dp[i] = 1;
		rep(j, 1, i - 1) if (p[j].x < p[i].x && p[j].y < p[i].y && p[j].z < p[i].z)
		{
			chkmax(dp[i], dp[j] + 1);
			ae(j, i);
		}
	}
	rep(i, 1, n) chkmax(ans, dp[i]);
	printf("%d\n", ans);
	ans = n;
	rep(i, 1, n)
	{
		ms(vis, 0);
		ans -= dfs(i);
	}
	printf("%d\n", ans);

	return 0;
}
