#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1001;
struct data
{
	int x, y, z;
}a[N];
int ans;
int b[N << 1][N << 1];
int f[N << 1];
bool bz[N << 1];
inline int read()
{
	int X = 0, w = 1; char ch = 0;
	while (ch<'0' || ch>'9') { if (ch == '-') w = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') X = (X << 3) + (X << 1) + ch - '0', ch = getchar();
	return X*w;
}
inline int max(int x, int y)
{
	return x > y ? x : y;
}
inline bool cmp(data x, data y)
{
	return x.x < y.x;
}
inline bool Hungary(int x)
{
	for (int i = 1; i <= b[x][0]; i++)
		if (!bz[b[x][i]])
		{
			bz[b[x][i]] = true;
			if (!f[b[x][i]] || Hungary(f[b[x][i]]))
			{
				f[b[x][i]] = x;
				return true;
			}
		}
	return false;
}
int main()
{
	freopen("missile.in", "r", stdin);
	freopen("missile.out", "w", stdout);
	int n = read();
	for (int i = 1; i <= n; i++) a[i].x = read(), a[i].y = read(), a[i].z = read();
	sort(a + 1, a + 1 + n, cmp);
	for (int i = 1; i <= n; i++)
		for (int j = f[i] = 1; j < i; j++)
			if (a[j].y < a[i].y && a[j].z < a[i].z)
			{
				f[i] = max(f[i], f[j] + 1);
				b[j << 1][++b[j << 1][0]] = i << 1 | 1;
			}
	for (int i = 1; i <= n; i++)
	{
		if (f[i] > ans) ans = f[i];
		f[i] = 0;
	}
	printf("%d\n", ans), ans = 0;
	for (int i = 2; i <= n << 1; i += 2)
	{
		memset(bz, false, sizeof(bz));
		if (Hungary(i)) ans++;
	}
	printf("%d", n - ans);
}
