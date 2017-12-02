#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

const int maxn = 210;

using namespace std;

int n = 0;
int ans = 1000000000;
int lis[maxn];
int num[maxn];
bool unlive[maxn];

void dfs(int f);

int main()
{
	freopen("zuma.in", "r", stdin);
	freopen("zuma.out", "w", stdout);
	char b;
	memset(unlive, 0, sizeof unlive);
	cin >> b;
	lis[n] = b - '0';
	num[n] = 1;
	while (cin >> b)
		if (b - '0' == lis[n])
			num[n]++;
		else
		{
			lis[++n] = b - '0';
			num[n] = 1;
		}
	dfs(0);
	printf("%d\n", ans);
	return 0;
}

void dfs(int f)
{
	int c = 0;
	while (unlive[c] && c <= n)
		c++;
	if (c > n)
	{
		ans = min(ans, f);
		return;
	}
	while (c <= n)
	{
		if (unlive[c])
		{
			c++;
			continue;
		}
		num[c]++;
		if (num[c] >= 3)
			unlive[c] = true;
		vector<pair<int, int> > vec;
		int l, r;
		l = r = c;
		l--;
		r++;
		while (l >= 0 && r <= n)
		{
			while (unlive[l] && l > 0)
				l--;
			while (unlive[r] && r < n)
				r++;
			if (lis[l] == lis[r])
			{
				if (num[l] + num[r] >= 3)
				{
					unlive[l] = unlive[r] = true;
					vec.push_back(make_pair(l, r));
				}
				else
				{
					num[l] += num[r];
					unlive[r] = true;
					break;
				}
			}
			l--;
			r++;
		}
		dfs(f + 1);
		if (l >= 0 && r <= n)
		{
			num[l] -= num[r];
			unlive[r] = false;
		}
		for (int i = 0; i < vec.size(); i++)
			unlive[vec[i].first] = unlive[vec[i].second] = false;
		if (num[c] >= 3)
			unlive[c] = false;
		num[c]--;
		c++;
	}
}

