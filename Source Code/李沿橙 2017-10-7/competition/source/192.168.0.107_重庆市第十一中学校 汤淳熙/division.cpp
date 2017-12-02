#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
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
const int MAXN = 1005;

int n, K,
	Colour[MAXN];

struct Brute_0 {
	Brute_0(void) { puts("1"); }
};

struct Brute_1 {
	int Colour[MAXN], Cnt;

	inline bool IsSqr(int x)
	{
		int a = sqrt(x);

		if (x == a * a) return true;
		else return false;
	}

	inline bool IsOk(int From, int To)
	{
		int TempCnt = 0;

		for (int i = From; i <= To - 1; ++i)
			if (IsSqr(Colour[i] + Colour[i + 1]))
				++TempCnt;

		if (TempCnt <= K) return true;
		else return false;
	}

	Brute_1(void) : Cnt(1)
	{
		for (int i = 1; i <= n; ++i)
			scanf("%d", Colour + i);

		if (IsOk(1, n)) {
			puts("1");
			return;
		}

		stack<int> Ans, EmptyStk;

		int Lft = 1, Rgt = n;
		while (Lft <= Rgt) {
			Ans = EmptyStk;

			int Mdl = (Lft + Rgt) / 2,
				From = n;
			do {
				int i = From - 1;
				for (; i >= 1; --i) {
					if (!IsOk(i, From)) {
						Ans.push(i);
						break;
					}
				}

                From = i;
			} while (From >= 1);

			if (Ans.size() + 1 <= Mdl) Rgt = Mdl - 1;
			else Lft = Mdl + 1;
		}

        cout << (Ans.size() + 1) <<endl;
        while (!Ans.empty()) {
            cout << Ans.top() << ' ';
            Ans.pop();
        }
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
#endif // LOCAL

	scanf("%d %d", &n, &K);

		delete new Brute_1();

	return 0;
}
