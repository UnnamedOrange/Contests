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
const int MAXN = 1e6 + 5,
	LMT = 20;

long long a, b;

struct Vtx {
	Vtx *Next;
	int To;

	Vtx(void) : Next(NULL) {}
};

struct VtxHead : Vtx {
	Vtx *Head;

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

	VtxHead(void) : Head(NULL) {}
} Graph[MAXN];

int Dpt[MAXN], Ast[MAXN][LMT];
int Lca(int x, int y)
{
	if (Dpt[x] < Dpt[y])
		swap(x, y);

	int k = 0;
	while ((1 << k) < Dpt[x]) ++k;

	for (int i = k; i >= 0; --i)
		if (Dpt[x] - (1 << i) >= Dpt[y])
			x = Ast[x][i];

	if (x == y)
		return x;

	for (int i = k; i >= 0; --i)
		if (Ast[x][i] != Ast[y][i]) {
			x = Ast[x][i];
			y = Ast[y][i];
		}

	return Ast[x][0];
}

struct Initialise {
	int Rabbit[MAXN], Amt, Pre, Idx;
	deque<int> Baby;

	void Search(int x)
	{
		for (Vtx *i = Graph[x].Head;
			i; i = i->Next) {
			if (Dpt[i->To] == 0) {
				Dpt[i->To] = Dpt[x] + 1;
				Ast[i->To][0] = x;

				Search(i->To);
			}
		}
	}

	inline void Init(void) {
		Search(1);

		for (int Level = 1; (1 << Level) <= Idx; ++Level)
			for (int i = 1; i <= Idx; ++i)
				Ast[i][Level] =
				Ast[
					Ast[i][Level - 1]
				][Level - 1];
	}

	Initialise(void) : Pre(1), Amt(1), Idx(1)
	{
		Rabbit[1] = 1;

		bool aFind, bFind = aFind = false;

		while (Idx <= 8e5) {
			while (!Baby.empty()) {
				Rabbit[++Amt] = Baby.front();
				Baby.pop_front();
			}

			for (int i = 1; i <= Pre; ++i) {
				Graph[Rabbit[i]] += ++Idx;

				if (Idx == a) aFind = true;
				if (Idx == b) bFind = true;

				Baby.push_back(Idx);
			}

			Pre = Amt;
		}

		Init();
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);
#endif // LOCAL

	delete new Initialise();

	int m;
	scanf("%d", &m);

	while (m--) {
		scanf("%lld %lld", &a, &b);

		if (a == b) printf("%d\n", a);
		else if (abs(a - b) <= 1) puts("1");
		else if (a > 1e6 || b > 1e6) printf("%lld", min(a, b));
		else printf("%d\n", Lca(a, b));
	}

	return 0;
}
