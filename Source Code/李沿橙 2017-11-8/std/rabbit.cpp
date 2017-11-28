#include <cstdio>
#include <cstring>
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;

const int maxn = 2010;
struct data {
	int adj, next;
} r[10 * maxn];
int g[maxn], tot, du[maxn], rt;
void ins(int a, int b)
{
	r[++tot].adj = b;
	r[tot].next = g[a];
	g[a] = tot;
}
int n, m, k;

struct road {
	bool circle;
	int len;
};
road d[maxn], d2[maxn];
int cnt;

int calc(int len, int t)
{
	if (len <= 0) return 0;
	return (len - 1) / (t * 2 + 1) + 1;
}

bool check(int t)
{
	int mind = n + 1;
	for (int i = 0; i < cnt; ++i)
	{
		for (int kp = 0; kp <= d[i].len && kp <= t; ++kp)
		{
			int tot;
			if (!d[i].circle)
				tot = calc(d[i].len - kp - t, t);
			else tot = calc(d[i].len - kp - t + (kp - t), t);
			++tot;
			for (int j = 0; j < cnt; ++j)
			if (j != i)
			{
				if (!d[j].circle)
					tot += calc(d[j].len + (kp - t), t);
				else
					tot += calc(d[j].len + 2 * (kp - t), t);
			}
			mind = min(mind, tot);
		}
	}
	return mind <= k;
}

void binary()
{
	int l = 0, r = n;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", r);
}

void init();
int main()
{
	init();
	binary();
	return 0;
}
bool col[maxn];
int t0;
void dfs(int x)
{
	col[x] = 1;
	++d[cnt].len;
	for (int p = g[x]; p != -1; p = r[p].next)
		if (col[r[p].adj] == 0)
			dfs(r[p].adj);
		else if (r[p].adj == rt && x != t0)
			d[cnt].circle = 1;
}
void init()
{
	scanf("%d%d%d", &n, &m, &k);
	memset(g, 255, sizeof(g));
	tot = -1;
	memset(du, 0, sizeof(du));
	rt = 1;
	for (int i = 1; i <= m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		++du[a];
		if (du[a] > 2) rt = a;
		++du[b];
		if (du[b] > 2) rt = b;
		ins(a, b);
		ins(b, a);
	}
	cnt = 0;
	memset(col, 0, sizeof(col));
	col[rt] = 1;
	for (int i = g[rt]; i != -1; i = r[i].next)
		if (col[r[i].adj] == 0)
		{
			t0 = r[i].adj;
			d[cnt].circle = 0;
			d[cnt].len = 0;
			dfs(r[i].adj);
			++cnt;
		}
}
