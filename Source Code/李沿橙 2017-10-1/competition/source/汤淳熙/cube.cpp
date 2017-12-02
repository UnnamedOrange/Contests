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
const int MAXN = 1005;

int Ins;

struct Brute_1 {
	int Where[25];
	deque<int> Buc[25];

	Brute_1(void)
	{
		for (int i = 1; i <= 20; ++i) {
			Buc[i].push_back(i);
			Where[i] = i;
		}

		while (Ins--) {
			char Type;
			cin >> Type;

			if (Type == 'M') {
				int From, To;
				scanf("%d %d", &From, &To);

				int WheFrom = Where[From],
					WheTo = Where[To];

				while (!Buc[WheFrom].empty()) {
					int x = Buc[WheFrom].front();
					Buc[WheFrom].pop_front();
					Buc[WheTo].push_back(x);
					Where[x] = WheTo;
				}
			} else {
				int x;
				scanf("%d", &x);

				int Cnt = 0;
				for (deque<int>::iterator i = Buc[Where[x]].begin();
					i != Buc[Where[x]].end(); ++i)
					if (*i == x) break;
					else ++Cnt;

				printf("%d\n", Cnt);
			}
		}
	}
};

struct Brute_2 {
	int Where[MAXN], Order[MAXN], Size[MAXN];

	Brute_2(void)
	{
		for (int i = 1; i <= 1000; ++i) {
			Where[i] = i;
			Order[i] = 0;
			Size[i] = 1;
		}

		while (Ins--) {
			char Type;
			cin >> Type;

			if (Type == 'M') {
				int F, T;
				scanf("%d %d", &F, &T);

				int FIdx = Where[F],
					TIdx = Where[T];

				int Lgt = 0;
				for (int i = 1; i <= 1000; ++i)
					if (Where[i] == FIdx) {
						Where[i] = TIdx;
						Order[i] += Size[TIdx];
						++Lgt;
					}

				Size[TIdx] += Lgt;
				Size[FIdx] = 0;
			} else {
				int x;
				scanf("%d", &x);

				printf("%d\n", Order[x]);
			}
		}
	}
};

struct Main {

	Main(void)
	{

	}
};

int main(void)
{
#ifndef LOCAL
	freopen("cube.in", "r", stdin);
	freopen("cube.out", "w", stdout);
#endif // LOCAL

	scanf("%d", &Ins);

	if (Ins <= 20)
		delete new Brute_1();
	else if (Ins <= 1000)
		delete new Brute_2();
	else delete new Main();

	return 0;
}

/*
6
M 1 6
C 1
M 2 4
M 2 6
C 3
C 4

1
2
3
4
5
6

*/
