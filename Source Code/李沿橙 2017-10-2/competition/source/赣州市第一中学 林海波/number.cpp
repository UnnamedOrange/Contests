#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 10000010;

using namespace std;

int n;
int ans = 0;
int a[10];
int b[10];
int num[maxn] = { 0 };

bool comp(int * c, int * d, int len);

int main()
{
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int t = i;
		int len = 0;
		while (t != 0)
		{
			a[len++] = t % 10;
			t /= 10;
		}
		for (int j = 0; j < len; j++)
			b[j] = a[j];
		sort(b, b + len);
		while (prev_permutation(a, a + len))
			num[i]++;
		unique(num, num + len);
		ans += num[i];
	}
	printf("%d\n", ans*2);
	return 0;
}

bool comp(int c[], int d[], int len)
{
	for (int i = 0; i < len; i++)
		if (c[i] != d[i])
			return false;
	return true;
}

