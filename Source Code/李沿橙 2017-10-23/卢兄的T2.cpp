#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 1001000;
int n, maxc, f[maxn], c[maxn], v[maxn], stack[12][12][21000], top[12][12];
inline int getans(int i, int j)
{
	return f[j] + (i - j) / c[j] * v[j];
}
inline double getx(int i, int j)
{
	return v[j] == v[i] ? 1e9 + 10 :
		(double)(f[i] - f[j] - v[i] * (i / c[i]) + v[j] * (j / c[j])) /
		//----------------------------------------------------------------
		(double)(v[j] - v[i]);
}

inline int read()
{
	int X = 0, w = 1;
	char ch = 0;
	while (ch<'0' || ch>'9')
	{
		if (ch == '-') w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') X = (X << 3) + (X << 1) + ch - '0', ch = getchar();
	return X*w;
}
inline void print(int x)
{
	if (x >= 10) print(x / 10);
	putchar(x % 10 + 48);
}
int main()
{
	freopen("bus.in", "r", stdin);
	freopen("bus.out", "w", stdout);
	n = read(), maxc = read();
	for (int i = 0; i < n; i++)
		c[i] = read(), v[i] = read();
	memset(f, 127, sizeof(f));
	f[0] = 0;

	for (int i = 0; i < n; i++)
	{
		int step = c[i], mod = i%c[i];
		while (top[step][mod] && v[stack[step][mod][top[step][mod]]] >= v[i])
			top[step][mod]--;
		while (top[step][mod] > 1 &&
			getx(i, stack[step][mod][top[step][mod]]) >=
			getx(stack[step][mod][top[step][mod]], stack[step][mod][top[step][mod] - 1]))
			top[step][mod]--;

		stack[step][mod][++top[step][mod]] = i;
		for (int s = 1; mod = (i + 1) % s, s <= maxc; s++) //s:step
		{
			while (top[s][mod] > 1 &&
				getans(i + 1, stack[s][mod][top[s][mod]]) >=
				getans(i + 1, stack[s][mod][top[s][mod] - 1]))
				top[s][mod]--;
			if (top[s][mod])
				f[i + 1] = min(f[i + 1],
					getans(i + 1, stack[s][mod][top[s][mod]]));
		}
	}

	for (int i = 1; i <= n; i++, printf(" "))
		if (f[i] >= 1e9) printf("-1");
		else print(f[i]);
}
