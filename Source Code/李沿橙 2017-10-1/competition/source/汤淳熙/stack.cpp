#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <set>
#include <map>
using namespace std;
const int MAXN = 1005,
	MOD = 7;

int n;

struct Brute {
	int Prog, Ans, Cnt;

	int Stack[MAXN], *Pst = Stack;

	void Procedure(void)
	{
		if (Cnt == n) {
			Ans = (Ans + 1) % MOD;
			return;
		}

		int *TempPst = Pst;
		if (Prog < n) {
			++Prog;
			*Pst = Prog;
			++Pst;

			Procedure();

			--Prog;
			Pst = TempPst;
		}

		if (Pst != Stack) {
			--Pst;
			++Cnt;

			Procedure();

			--Cnt;
			Pst = TempPst;
		}
	}

	Brute(void) : Cnt(0), Ans(0), Prog(1)
	{
		*Pst = 1;
		++Pst;

		Procedure();

		printf("%d\n", Ans);
	}
};

struct Main {
	int Dyn[MAXN][MAXN];
	bool IsCalc[MAXN][MAXN];

	int Calc(int x, int y)
	{
		if (x < 0) return 0;
		if (IsCalc[x][y]) return Dyn[x][y];
		else if (y == 0) return 1;

		IsCalc[x][y] = true;

		int a = Calc(x + 1, y - 1) % MOD,
			b = Calc(x - 1, y) % MOD;

		Dyn[x][y] = (a + b) % MOD;

		return Dyn[x][y];
	}

	Main(void) : IsCalc(), Dyn()
	{
		if (n == 0) {
			cout << "1" << endl;
			exit(0);
		}

		cout << Calc(1, n - 1) << endl;
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("stack.in", "r", stdin);
	freopen("stack.out", "w", stdout);
#endif // LOCAL

	scanf("%d", &n);

	delete new Main();

	return 0;
}
