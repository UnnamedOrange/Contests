#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(1e5) + 5;
int n, q;
LL a[maxn];

#define RunInstance(x) delete new x
struct brute
{
	int idx[maxn];
	int left[maxn];
	int right[maxn];

	static bool comp(const int& x, const int& y)
	{
		return a[x] < a[y];
	}

	LL solve()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n, comp);
		left[0] = right[n] = 0;
		for (int i = 1; i < n; i++)
		{
			left[i + 1] = i;
			right[i] = i + 1;
		}

		LL ans = 0;
		for (int i = 1; i < n; i++)
		{
			int pos = idx[i];
			if (left[pos] && right[pos])
			{
				right[left[pos]] = right[pos];
				left[right[pos]] = left[pos];
			}
			else if (left[pos])
			{
				int from = left[pos] + 1;
				for (int i = from; i < pos; i++)
					ans += a[pos] - a[i];
				right[left[pos]] = 0;
			}
			else if (right[pos])
			{
				int to = right[pos];
				for (int i = pos + 1; i < to; i++)
					ans += a[pos] - a[i];
				left[right[pos]] = 0;
			}
		}
		return ans;
	}

	brute()
	{
		while (q--)
		{
			char ins[5];
			scanf("%s", ins);
			if (ins[0] == 'P')
				printOut(solve());
			else if (ins[0] == 'U')
			{
				int pos = readIn();
				int val = readIn();
				a[pos] += val;
			}
		}
	}
};
struct work
{
	int idx[maxn];
	int left[maxn];
	int right[maxn];

	static bool comp(const int& x, const int& y)
	{
		return a[x] < a[y];
	}

	std::set<int> set;
	LL ans;
	struct BIT
	{
		LL bit[maxn];
		static inline int lowbit(int x)
		{
			return x & -x;
		}
		BIT() : bit() {}
		void add(int pos, int val)
		{
			while (pos <= n)
			{
				bit[pos] += val;
				pos += lowbit(pos);
			}
		}
		LL query(int pos)
		{
			LL ret = 0;
			while (pos)
			{
				ret += bit[pos];
				pos ^= lowbit(pos);
			}
			return ret;
		}
		LL query(int l, int r)
		{
			if (l > r) return 0;
			return query(r) - query(l - 1);
		}
	} bit;

	work() : ans()
	{
		for (int i = 1; i <= n; i++)
			bit.add(i, a[i]);
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + n, comp);
		left[0] = right[n] = 0;
		for (int i = 1; i < n; i++)
		{
			left[i + 1] = i;
			right[i] = i + 1;
		}

		for (int i = 1; i < n; i++)
		{
			int pos = idx[i];
			if (left[pos] && right[pos])
			{
				right[left[pos]] = right[pos];
				left[right[pos]] = left[pos];
			}
			else if (left[pos])
			{
				int from = left[pos] + 1;
				for (int i = from; i < pos; i++)
					ans += a[pos] - a[i];
				right[left[pos]] = 0;

				set.insert(pos);
			}
			else if (right[pos])
			{
				int to = right[pos];
				for (int i = pos + 1; i < to; i++)
					ans += a[pos] - a[i];
				left[right[pos]] = 0;

				set.insert(pos);
			}
		}

		int center = idx[n];
		set.insert(idx[n]);

		typedef std::set<int>::iterator IT;
		while (q--)
		{
			char ins[5];
			scanf("%s", ins);
			if (ins[0] == 'P')
				printOut(ans);
			else if (ins[0] == 'U')
			{
				int pos = readIn();
				int val = readIn();

				if (set.count(pos))
				{
					if (pos == center)
					{
						a[pos] += val;
					}
					else if (pos < center)
					{
						IT it;
						LL preHeight = a[pos];
						int prePos = pos;
						while (true)
						{
							it = set.find(pos);
							it++;
							if (*it == center) break;
							if (a[pos] + val > a[*it])
							{
								ans -= preHeight * (*it - prePos - 1) - bit.query(prePos + 1, *it - 1);
								prePos = *it;
								preHeight = a[prePos];
								set.erase(it);
							}
							else break;
						}
						it = set.find(pos);
						it++;
						ans -= preHeight * (*it - prePos - 1) - bit.query(prePos + 1, *it - 1);
						a[pos] += val;
						if (a[pos] > a[center])
						{
							ans += a[center] * (center - pos - 1) - bit.query(pos + 1, center - 1);
							center = pos;
						}
						else
						{
							ans += a[pos] * (*it - pos - 1) - bit.query(pos + 1, *it - 1);
						}
					}
					else if (pos > center)
					{
						IT it;
						LL preHeight = a[pos];
						int prePos = pos;
						while (true)
						{
							it = set.find(pos);
							it--;
							if (*it == center) break;
							if (a[pos] + val > a[*it])
							{
								ans -= preHeight * (prePos - *it - 1) - bit.query(*it + 1, prePos - 1);
								prePos = *it;
								preHeight = a[prePos];
								set.erase(it);
							}
							else break;
						}
						it = set.find(pos);
						it--;
						ans -= preHeight * (prePos - *it - 1) - bit.query(*it + 1, prePos - 1);
						a[pos] += val;
						if (a[pos] > a[center])
						{
							ans += a[center] * (pos - center - 1) - bit.query(center + 1, pos - 1);
							center = pos;
						}
						else
						{
							ans += a[pos] * (pos - *it - 1) - bit.query(*it + 1, pos - 1);
						}
					}
					bit.add(pos, val);
				}
				else
				{
					if (pos < center)
					{
						IT it = set.upper_bound(pos);
						it--;
						int prePos = *it;
						LL preHeight = a[prePos];
						it++;
						ans -= preHeight * (*it - prePos - 1) - bit.query(prePos + 1, *it - 1);

						if (a[prePos] > a[pos] + val)
						{
							a[pos] += val;
							bit.add(pos, val);
							ans += preHeight * (*it - prePos - 1) - bit.query(prePos + 1, *it - 1);
						}
						else
						{
							ans += preHeight * (pos - prePos - 1) - bit.query(prePos + 1, pos - 1);

							set.insert(pos);
							it = set.find(pos);
							it++;
							a[pos] += val;
							ans += a[pos] * (*it - pos - 1) - bit.query(pos + 1, *it - 1);
							prePos = pos;
							preHeight = a[pos];
							while (true)
							{
								it = set.find(pos);
								it++;
								if (*it == center) break;
								if (a[pos] > a[*it])
								{
									ans -= preHeight * (*it - prePos - 1) - bit.query(prePos + 1, *it - 1);
									prePos = *it;
									preHeight = a[prePos];
									set.erase(it);
								}
								else break;
							}
							it = set.find(pos);
							it++;
							ans -= preHeight * (*it - prePos - 1) - bit.query(prePos + 1, *it - 1);
							if (a[pos] > a[center])
							{
								ans += a[center] * (center - pos - 1) - bit.query(pos + 1, center - 1);
								center = pos;
							}
							else
							{
								ans += a[pos] * (*it - pos - 1) - bit.query(pos + 1, *it - 1);
							}
							bit.add(pos, val);
						}
					}
					else
					{
						IT it = set.lower_bound(pos);
						int prePos = *it;
						LL preHeight = a[prePos];
						it--;
						ans -= preHeight * (prePos - *it - 1) - bit.query(*it + 1, prePos - 1);

						if (a[prePos] > a[pos] + val)
						{
							a[pos] += val;
							bit.add(pos, val);
							ans += preHeight * (prePos - *it - 1) - bit.query(*it + 1, prePos - 1);
						}
						else
						{
							ans += preHeight * (prePos - pos - 1) - bit.query(pos + 1, prePos - 1);

							set.insert(pos);
							it = set.find(pos);
							it--;
							a[pos] += val;
							ans += a[pos] * (pos - *it - 1) - bit.query(*it + 1, pos - 1);
							preHeight = a[pos];
							prePos = pos;
							while (true)
							{
								it = set.find(pos);
								it--;
								if (*it == center) break;
								if (a[pos] > a[*it])
								{
									ans -= preHeight * (prePos - *it - 1) - bit.query(*it + 1, prePos - 1);
									prePos = *it;
									preHeight = a[prePos];
									set.erase(it);
								}
								else break;
							}
							it = set.find(pos);
							it--;
							ans -= preHeight * (prePos - *it - 1) - bit.query(*it + 1, prePos - 1);
							if (a[pos] > a[center])
							{
								ans += a[center] * (pos - center - 1) - bit.query(center + 1, pos - 1);
								center = pos;
							}
							else
							{
								ans += a[pos] * (pos - *it - 1) - bit.query(*it + 1, pos - 1);
							}
							bit.add(pos, val);
						}
					}
				}
			}
		}
	}
};

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();

	if (n <= 3000)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	run();
	return 0;
}