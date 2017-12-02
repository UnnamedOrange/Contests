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
const int MAXN = 1e5 + 5,
	LMT = log2(MAXN);
const long long MOD = 1e9 + 7;

int n, Val[MAXN];

struct Vtx {
	int To;
	Vtx *Next;

	Vtx(void) : Next(NULL) {}
};

struct VtxHead : Vtx {
	Vtx *Head;

	void operator += (int To)
	{
		if (Head == NULL) {
			Next = new Vtx();
			Next->To = To;
			Head = Next;
		} else {
			Next->Next = new Vtx();
			Next = Next->Next;	
			Next->To = To;
		}
	}
} Graph[MAXN];

int Ast[MAXN];
int GetAst(int x)
{
	if (x == Ast[x]) return x;
	return Ast[x] = GetAst(Ast[x]);
}

int Dpt[MAXN], Dis[MAXN], Father[MAXN][LMT];
void Search(int x)
{
	Dpt[x] = Dpt[Father[x][0]] + 1;
	Dis[x] = Dis[Father[x][0]] + Val[x];

	for (int i = 1; i <= LMT; ++i)
		Father[x][i] = Father[Father[x][i - 1]][i - 1];

	for (Vtx *i = Graph[x].Head;
		i; i = i->Next ) {
		if (i->To == Father[x][0])
			continue;

		Father[i->To][0] = x;

		Search(i->To);
	}
}

inline int Lca(int x, int y)
{
	if (Dpt[x] < Dpt[y])
		swap(x, y);

	int k = 0;
	while ((1 << k) < Dpt[x]) ++k;

	for (int i = k; i >= 0; --i)
		if (Dpt[x] - (1 << i) >= Dpt[y])
			x = Father[x][i];

	if (x == y)
		return x;

	for (int i = k; i >= 0; --i)
		if (Father[x][i] != Father[y][i]) {
			x = Father[x][i];
			y = Father[y][i];
		}

	return Father[x][0];
}

inline int CalcDis(int x, int y)
{
	int CrtLca = Lca(x, y);
	return Dis[x] + Dis[y] -
		Dis[CrtLca] -
		Dis[Father[CrtLca][0]];
}

inline int InvPow(int x, int y)
{
	int Ans = 1;

	while (y) {
		if (y & 1) Ans = (long long)Ans * x % MOD;
		x = (long long)x * x % MOD;
		y >>= 1;
	}

	return Ans;
}

int Qry[MAXN];
struct Unit {
	int x, y;
} QryBuc[MAXN];

int Mul[MAXN],
	Lgt[MAXN], Size[MAXN],
	aBuc[MAXN], bBuc[MAXN];
struct Main {

	Main(void)
	{
		scanf("%d", &n);

		Mul[n] = 1;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", Val + i);
			Mul[n] = (long long)Mul[n] * Val[i] % MOD;

			Ast[i] = i;
			Dpt[i] = Size[i] = 1;

			Dis[i] = Lgt[i] = Val[i];

			aBuc[i] = bBuc[i] = i;
		}

		for (int i = 1; i < n; ++i)
			scanf("%d %d",
				&QryBuc[i].x, &QryBuc[i].y);

		for (int i = 1; i < n; ++i)
			scanf("%d", Qry + i);

		for (int i = n - 1; i > 0; --i) {
			int x = QryBuc[Qry[i]].x,
				y = QryBuc[Qry[i]].y;

			if (Size[GetAst(x)] > Size[GetAst(y)])
				swap(x, y);

			int xAst = GetAst(x),
				yAst = GetAst(y),
				x_1 = aBuc[xAst], x_2 = bBuc[xAst],
				y_1 = aBuc[yAst], y_2 = bBuc[yAst];

			Mul[i] = (long long)Mul[i + 1] *
				InvPow(Lgt[xAst], MOD - 2) % MOD *
				InvPow(Lgt[yAst], MOD - 2) % MOD;

			Graph[x] += y; // add edge
			Graph[y] += x;

			Father[x][0] = y;
			Search(x);

			Size[yAst] += Size[xAst];
			Ast[xAst] = Ast[yAst]; // merge

			if (Lgt[xAst] >= Lgt[yAst]) {
				Lgt[yAst] = Lgt[xAst];
				aBuc[yAst] = x_1;
				bBuc[yAst] = y_1;
			}

			int CrtDis = CalcDis(x_1, x_2); // enum
			if (CrtDis > Lgt[yAst]) {
				Lgt[yAst] = CrtDis;
				aBuc[yAst] = x_1;
				bBuc[yAst] = x_2;
			} CrtDis = CalcDis(x_1, y_2);
			if (CrtDis > Lgt[yAst]) {
				Lgt[yAst] = CrtDis;
				aBuc[yAst] = x_1;
				bBuc[yAst] = y_2;
			} CrtDis = CalcDis(y_1, x_2);
			if (CrtDis > Lgt[yAst]) {
				Lgt[yAst] = CrtDis;
				aBuc[yAst] = y_1;
				bBuc[yAst] = x_2;
			} CrtDis = CalcDis(y_1, y_2);
			if (CrtDis > Lgt[yAst]) {
				Lgt[yAst] = CrtDis;
				aBuc[yAst] = y_1;
				bBuc[yAst] = y_2;
			}

			Mul[i] = (long long)Mul[i] * Lgt[yAst] % MOD;
		}

		for (int i = 1; i <= n; ++i)
			printf("%d\n", Mul[i]);
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("forest.in", "r", stdin);
	freopen("forest.out", "w", stdout);
#endif // LOCAL

	delete new Main();

	return 0;
}
