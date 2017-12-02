#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 100010;
const int inf = 1000000000;

using namespace std;

int n = 0;
int ans = inf;
int s[maxn];

int main()
{
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
	char ch;
	s[0] = 0;
	n = 1;
	while (cin >> ch)
	{
		s[n] = s[n - 1] + ch - '0';
		n++;
	}
	n--;
	for (int i = 0; i <= n; i++)
		ans = min(ans, s[i] + ((n - i) - (s[n] - s[i])));
	printf("%d\n", ans);
	return 0;
}

