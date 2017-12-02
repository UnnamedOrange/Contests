#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>

using namespace std;

int m;
int a, b;
long long f[65];

int bound(int n);

int main()
{
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);
	f[0] = 1;
	f[1] = 1;
	for (int i = 2; i < 65; i++)
		f[i] = f[i - 1] + f[i - 2];
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &a, &b);
		while (a != b)
		{
			if (a > b)
				swap(a, b);
			int b_bound = bound(b);
			b -= f[b_bound];
		}
		printf("%d\n", a);
	}
	return 0;
}

int bound(int n)
{
	int l = 1;
	int r = 60;
	while (l + 1 < r)
	{
		int mid = (l + r + 1) / 2;
		if (f[mid] < n)
			l = mid;
		else
			r = mid - 1;
	}
	if (f[r] < n)
		l = r;
	return l;
}

