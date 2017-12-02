#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <ctime>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;
const int MAXL = 1e6 + 5;
/*

n 个数字 {d_n} 2、3
k 次操作
	条件：找到最小的的 x 使得 d_x = 2 并且 d_{x + 1} = 3
	操作：如果 x 为奇数，就令 d_{x + 1} = 2，否则就令 d_x = 3
 */

int n, k;
char Nbr[MAXL];

struct Brute {
	struct Unit {
		int x;

		bool operator < (const Unit &a) const
		{
			return x > a.x;
		}
	};

	priority_queue<Unit> oQ, eQ;

	inline void Initialise(void)
	{
		for (int i = 0; i < n - 1; ++i)
			if (Nbr[i] == '2' && Nbr[i + 1] == '3')
				if ((i + 1) & 1) oQ.push((Unit) { i });
				else eQ.push((Unit) { i });
	}

	Brute(void)
	{
		Initialise();

		while (k--) {
			Unit oT = { INT_MAX }, eT = { INT_MAX };
			if (!oQ.empty())
				oT = oQ.top();
			if (!eQ.empty())
				eT = eQ.top();

			if (oT.x < eT.x) {
				oQ.pop();
				if (Nbr[oT.x + 2] == '3')
					eQ.push((Unit) { oT.x + 1 });
				Nbr[oT.x + 1] = '2';
			} else if (eT.x < oT.x) {
				eQ.pop();
				if (Nbr[eT.x - 1] == '2')
					oQ.push((Unit) { eT.x - 1});
				Nbr[eT.x] = '3';
			}
		}

		printf("%s\n", Nbr);
	}
};

struct Main {
	int Cnt;

	Main(void) : Cnt(0)
	{
		for (int i = 0; i < n - 1 && Cnt != k; ++i)
			if (Nbr[i] == '2' && Nbr[i + 1] == '3') {
				if (((i + 1)) & 1 && Nbr[i + 2] == '3') {
					char Temp = Nbr[i];
					Nbr[i] = '\0';
					printf("%s", Nbr);

					int Left = k - Cnt;
					if (Left & 1) {
						printf("223%s\n", Nbr + i + 3);
						return;
					} else {
						Nbr[i] = Temp;
						printf("%s", Nbr + i);
						return;
					}
				}

				++Cnt;
				if ((i + 1) & 1) {
					Nbr[i + 1] = '2';
				} else {
					Nbr[i] = '3';
					i -= 2;
				}
			} else if (((i + 1) & 1) && Nbr[i] == '2' &&
				Nbr[i + 1] == '2' && Nbr[i + 2] == '3') {
					char Temp = Nbr[i];
                    Nbr[i] = '\0';
                    printf("%s", Nbr);

                    int Left = k - Cnt;
                    if (Left & 1) {
						printf("233%s\n", Nbr + i + 3);
						return;
					} else {
						Nbr[i] = Temp;
						printf("%s", Nbr + i);
						return;
					}
				}

		printf("%s\n", Nbr);
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("trans.in", "r", stdin);
	freopen("trans.out", "w", stdout);
#endif // LOCAL

	while (scanf("%d %d", &n, &k) == 2) {
		cin >> Nbr;

		delete new Main();
	}

	return 0;
}
