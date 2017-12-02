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
const int MAXN = 1e5 + 5;

int n, k, t;

struct Brute {
	struct Vtx {
		Vtx *Next;
		int To;

		Vtx(void) : Next(NULL) {}
	};

	struct VtxHead : Vtx {
		Vtx *Head;
		bool IsCover;
		int Degree;

		void operator += (int To)
		{
			if (!Head) {
				Next = new Vtx();
				Next->To = To;
				Head = Next;
			} else {
				Next->Next = new Vtx();
				Next = Next->Next;
				Next->To = To;
			}
		}

		bool operator < (const VtxHead &a) const
		{
			return Degree < a.Degree;
		}

		VtxHead(void) :
			Head(NULL), IsCover(false), Degree(0) {}
	} Graph[MAXN];

	int Cnt;

	priority_queue<VtxHead> Travel;
	void Cover(VtxHead x, int Lft = k)
	{
		if (Lft == 0) {
			++Cnt;
			Travel.push(x);
			return;
		}

		for (Vtx *i = x.Head;
			i; i = i->Next) {
			if (Graph[i->To].IsCover) continue;

			Graph[i->To].IsCover = true;
			Cover(Graph[i->To], Lft - 1);
		}
	}

	void Search(int x)
	{
		++Cnt;
		Travel.push(Graph[x]);
		Graph[x].IsCover = true;

		while (!Travel.empty()) {
			VtxHead y = Travel.top();
			Travel.pop();

			for (Vtx *i = y.Head;
				i; i = i->Next) {
				Graph[i->To].IsCover = true;
				Cover(Graph[i->To]);
			}
		}
	}

    int f[MAXN];

	Brute(void) : Cnt(0), f()
	{
		scanf("%d %d %d", &n, &k, &t);

		if (k == 0) printf("%d\n", n);
		else {
			for (int i = 1; i <= n - 1; ++i) {
				int u, v;
				scanf("%d %d", &u, &v);

				++Graph[u].Degree;
				++Graph[v].Degree;

				Graph[u] += v;
				Graph[v] += u;
			}

			int MaxVal = INT_MIN, MaxIdx = -1;
			for (int i = 1; i <= n; ++i)
				if (Graph[i].Degree > MaxVal) {
					MaxIdx = i;
					MaxVal = Graph[i].Degree;
				}

			Search(MaxIdx);

			cout << Cnt << endl;
		}
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("general.in", "r", stdin);
	freopen("general.out", "w", stdout);
#endif // LOCAL

	delete new Brute();

	return 0;
}

/*

9 2 1
1 2
2 3
1 6
6 7
6 8
8 9
1 4
4 5

*/
