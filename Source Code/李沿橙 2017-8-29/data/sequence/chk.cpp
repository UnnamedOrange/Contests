#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 200100;

int n;
int p[maxn + 5];

inline bool check(const string &s)
{
	int balance = 0;
	REP(i, 0, n)
	{
		balance += s[i] == '(' ? 1 : -1;
		if (balance < 0) return 0;
	}
	return !balance;
}

string s, t;

int main(int argc, char *argv[])
{
	registerLemonChecker(argc, argv);
	n = inf.readInt();
	n <<= 1;
	REP(i, 0, n) p[i] = inf.readInt(), --p[i];
	s = ouf.readToken();
	ensuref(SZ(s) == n, format("The length of s should be %d, but that of your s is %d.", n, SZ(s)).c_str());
	REP(i, 0, n) ensuref(s[i] == '(' || s[i] == ')', format("s[%d] = %c, which is neither '(' nor ')'.", i, s[i]).c_str()); 
	REP(i, 0, n) t += s[p[i]];
	ensuref(check(s), "s isn't a correct parentheses sequence.");
	ensuref(check(t), "t isn't a correct parentheses sequence.");
	quitf(_ok, "Correct answer.");
	return 0;
}

