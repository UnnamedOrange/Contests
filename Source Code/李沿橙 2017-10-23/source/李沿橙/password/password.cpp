#pragma G++ optimize("O3")
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT mod = INT(1e9) + 7;
const INT maxm = 9 + 5;
const INT maxG = 200 + 5;
INT m, G;
char g[maxm][maxG];
INT per[maxm];

INT q;
char s[maxG];
INT S;
INT n;

INT times1[maxm];
INT times2[maxm][maxm];

INT f[maxG];

void initFaliure()
{
	f[0] = f[1] = 0;
	for (int i = 1; i < S; i++)
	{
		INT pre = f[i];
		while (pre && s[i] != s[pre]) pre = f[pre];
		f[i + 1] = s[i] == s[pre] ? pre + 1 : 0;
	}
}
INT KMP(char* t, INT l, INT r)
{
	INT T = strlen(t);
	INT ret = 0;
	INT matched = 0;
	for (int i = 0; i < T; i++)
	{
		while (matched && t[i] != s[matched]) matched = f[matched];
		if (t[i] == s[matched]) matched++;
		if (matched == S)
		{
			if (l <= i && i <= r) ret++;
		}
	}
	return ret;
}

#define RunInstance(x) delete new x
struct work
{
	struct Status
	{
		typedef std::pair<INT, INT> c_status;
		c_status st[10];
		bool operator == (const Status& b) const
		{
			for (int i = 1; i <= m; i++)
				if (st[i] != b.st[i]) return false;
			return true;
		}
		const c_status& operator[] (INT x) const
		{
			return st[x];
		}
		c_status& operator[] (INT x)
		{
			return st[x];
		}
		Status()
		{
			for (int i = 1; i <= m; i++)
				st[i].first = st[i].second = i;
		}

		Status next()
		{
			Status ret;
			for (int i = 1; i < m; i++)
				ret[i] = (*this)[i + 1];
			ret[m].first = (*this)[per[1]].first;
			ret[m].second = (*this)[per[m]].second;
			return ret;
		}
	};

	struct Matrix
	{
		INT s[10][10];
		INT* operator[] (INT x)
		{
			return s[x];
		}
		const INT* operator[] (INT x) const
		{
			return s[x];
		}
		Matrix() : s() {}
		Matrix(bool unit) : s()
		{
			for (int i = 0; i <= m; i++) s[i][i] = 1;
		}

		Matrix operator* (const Matrix& b) const
		{
			const Matrix& a(*this);
			Matrix ret;
			for (int i = 0; i <= m; i++)
				for (int k = 0; k <= m; k++)
				{
					if (!a[i][k]) continue;
					for (int j = 0; j <= m; j++)
					{
						ret[i][j] = (ret[i][j] + a[i][k] * b[k][j] % mod) % mod;
					}
				}
			return ret;
		}
		Matrix operator^ (INT y) const
		{
			Matrix ret(true);
			Matrix x(*this);
			while (y)
			{
				if (y & 1) ret = ret * x;
				x = x * x;
				y >>= 1;
			}
			return ret;
		}
	};

	const Matrix& transit(const Status& S)
	{
		static Matrix base;
		static bool initialized;
		if (!initialized)
		{
			initialized = true;
			base[m][m] = 1;
			for (int i = 0; i < m - 1; i++)
				base[i + 1][i] = 1;
			for (int i = 0; i < m; i++)
				base[i][m - 1] = 1;
		}

		INT& extra = base[m][m - 1];
		extra = 0;
		for (int j = 1; j < m; j++)
		{
			extra += times2[S[per[j]].second][S[per[j + 1]].first];
		}
		return base;
	}
	INT getAns(const Matrix& x)
	{
		INT ans = 0;
		times1[m + 1] = 1;
		for (int i = 0; i < m + 1; i++)
			ans = (ans + times1[i + 1] * x[i][m - 1] % mod) % mod;
		return ans;
	}

	work()
	{
		while (q--)
		{
			scanf("%s", s);
			S = strlen(s);
			n = readIn();

			initFaliure();
			for (int i = 1; i <= m; i++)
				times1[i] = KMP(g[i], 0, G - 1);
			for (int i = 1; i <= m; i++)
				for (int j = 1; j <= m; j++)
				{
					char buffer[2 * maxG];
					sprintf(buffer, "%s%s", g[i], g[j]);
					times2[i][j] = KMP(buffer, G, G + S - 2);
				}

			if (n <= m)
			{
				cout << times1[n] << endl;
				continue;
			}

			std::vector<Status> s(1);
			INT start = -1;
			while (!~start)
			{
				s.push_back(s.back().next());
				for (int i = 0; i < s.size() - 1; i++)
					if (s[i] == s.back())
					{
						start = i;
						break;
					}
			}

			Matrix mul(true);

			INT to = std::min(n - m, start);
			for (int i = 0; i < to; i++)
				mul = mul * transit(s[i]);
			if (n - m <= start)
			{
				cout << getAns(mul) << endl;
				continue;
			}

			Matrix loop(true);
			for (int i = start; i < s.size() - 1; i++)
				loop = loop * transit(s[i]);
			loop = loop ^ ((n - m - 1 - start + 1) / (s.size() - start - 1));
			mul = mul * loop;

			INT times = (n - m - 1 - start + 1) % (s.size() - start - 1);
			for (int i = start; i < start + times; i++)
				mul = mul * transit(s[i]);

			cout << getAns(mul) << endl;
		}
	}
};
struct cheat
{
	typedef std::pair<INT, INT> Status;
	INT F[INT(1e6) + 5];
	Status status[INT(1e6) + 5];

	cheat() : F(), status()
	{
		while (q--)
		{
			scanf("%s", s);
			S = strlen(s);
			n = readIn();

			initFaliure();
			for (int i = 1; i <= m; i++)
				times1[i] = KMP(g[i], 0, G - 1);
			for (int i = 1; i <= m; i++)
			{
				for (int j = 1; j <= m; j++)
				{
					//if (i == j) continue; //1.多写了这一句
					char buffer[2 * maxG];
					sprintf(buffer, "%s%s", g[i], g[j]);
					times2[i][j] = KMP(buffer, G, G + S - 2);
				}
			}

			INT sumF = 0;
			for (int i = 1; i <= m; i++)
			{
				F[i] = times1[i];
				sumF += F[i];
				status[i] = std::make_pair(i, i);
			}
			for (int i = m + 1; i <= n; i++)
			{
				F[i] = sumF % mod;
				for (int j = 1; j < m; j++)
				{
					//2.差1错误
					//3.把j写成了i
					F[i] = (F[i] + times2[status[i - m + per[j] - 1].second][status[i - m + per[j + 1] - 1].first]) % mod;
				}
				//4.这一句放在了前面去了
				sumF = (sumF + F[i]) % mod;
				sumF = (sumF - F[i - m] + mod) % mod;
				//5.还是差1错误
				status[i] = std::make_pair(status[i - m + per[1] - 1].first, status[i - m + per[m] - 1].second);
			}
			cout << F[n] << endl;
		}
	}
};

void run()
{
	m = readIn();
	for (int i = 1; i <= m; i++)
		scanf("%s", g[i]);
	G = strlen(g[1]);
	for (int i = 1; i <= m; i++)
		per[i] = readIn();

	q = readIn();
	RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("password.in", "r", stdin);
	freopen("password.out", "w", stdout);
#endif
	run();
	return 0;
}
