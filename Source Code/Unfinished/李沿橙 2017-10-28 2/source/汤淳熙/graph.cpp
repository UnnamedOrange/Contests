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
#define END -1
using namespace std;
const int MAXN = 1e5 + 5;

int n;
struct Arc {
	int u, v, Next;
} Graph[MAXN * 4];

struct Main {
	int Head[MAXN], GraphIdx,
		DfsIdx, Low[MAXN], Dfn[MAXN],
		BlockBuc[MAXN], BlockCnt;
	bool IsIn[MAXN];

	stack<int> Travel;

	inline void Link(int x, int y)
	{
		Graph[GraphIdx].u = x;
		Graph[GraphIdx].v = y;
		Graph[GraphIdx].Next = Head[x];
		Head[x] = GraphIdx++;
	}

	void Tarjan(int Crt, int From)
	{
		Low[Crt] = Dfn[Crt] = ++DfsIdx;
		Travel.push(Crt);
		IsIn[Crt] = true;

//		bool IsStart = true;
		for (int i = Head[Crt];
			i != END; i = Graph[i].Next) {
			int To = Graph[i].v;

			if (/*IsStart && */To == From){
//				IsStart = false;
				continue;
			}

			if (!Dfn[To]) {
				Tarjan(To, Crt);
				if (Low[To] < Low[Crt])
					Low[Crt] = Low[To];
			} else if (IsIn[To] && Low[To] < Low[Crt])
				Low[Crt] = Low[To];
		}

		if (Low[Crt] == Dfn[Crt]) {
			++BlockCnt;

			int To;
			do {
				To = Travel.top();
				Travel.pop();
				IsIn[To] = false;

				BlockBuc[To] = BlockCnt;
			} while(To != Crt);
		}
	}

	int Degree[MAXN];
	inline void Compress(void)
	{
		for (int i = 0; i < GraphIdx; i += 2 ) {
			int u = BlockBuc[Graph[i].u],
				v = BlockBuc[Graph[i].v];

			if(u != v) {
				++Degree[u];
				++Degree[v];
			}
		}
	}

	Main(void) :
		Low(), Dfn(),
		BlockBuc(), IsIn(),
		GraphIdx(0), DfsIdx(0), BlockCnt(0)
	{
		int m;
		scanf("%d %d", &n, &m);

		memset(Head, END, sizeof Head);
		while (m--) {
			int x, y;
			scanf("%d %d", &x, &y);
			Link(x, y); Link(y, x);
		}

		Tarjan(1, -1);

		Compress();

		int Ans = 0;

		if (BlockCnt == 1){
			puts("0");
			return;
		}

		for (int i = 1; i <= BlockCnt; ++i)
			if (Degree[i] == 1)
				++Ans;

		printf("%d\n", (Ans + 1) / 2);
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
#endif // LOCAL

	delete new Main();

	return 0;
}

