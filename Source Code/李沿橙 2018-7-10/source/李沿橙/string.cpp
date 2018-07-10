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
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int mod = int(1e9) + 7;
const int maxn = int(3e5) + 5;
int n, m;
char str[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 105;
	ULL hash[maxN], revHash[maxN];
	ULL power[maxN];

	bool judge(int l, int r)
	{
		return hash[r] - hash[l - 1] * power[r - l + 1] ==
			revHash[l] - revHash[r + 1] * power[r - l + 1];
	}

	int ans[maxN][maxN];

	brute()
	{
		hash[0] = 0;
		for (int i = 1; i <= n; i++)
			hash[i] = hash[i - 1] * 131 + str[i];
		revHash[n + 1] = 0;
		for (int i = n; i; i--)
			revHash[i] = revHash[i + 1] * 131 + str[i];
		power[0] = 1;
		for (int i = 1; i < maxN; i++)
			power[i] = power[i - 1] * 131;

		for (int l = 1; l <= n; l++)
		{
			for (int r = l; r <= n; r++)
			{
				std::vector<ULL> temp;
				for (int i = l; i <= r; i++)
					for (int j = i; j <= r; j++)
						if (judge(i, j))
							temp.push_back(hash[j] - hash[i - 1] * power[j - i + 1]);
				std::sort(temp.begin(), temp.end());
				temp.resize(std::unique(temp.begin(), temp.end()) - temp.begin());
				ans[l][r] = temp.size();
			}
		}

		LL t = 0;
		for (int i = 1; i <= m; i++)
		{
			int l = readIn();
			int r = readIn();
			t = (t + (LL)ans[l][r] * i) % mod;
		}
		printOut(t);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	scanf("%s", str + 1);

	if (n <= 100)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("string.in", "r", stdin);
	freopen("string.out", "w", stdout);
#endif
	run();
	return 0;
}