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
const int MAXN = 50005,
	LMT = 10;
const long long MOD = 1e9 + 7;

int n,
	C[MAXN][LMT + 5];

inline void CalcC(void)
{
	for (int i = 1; i <= n; ++i) {
		C[i][0] = 1;

		int Limit = min(i, LMT);
		for (int j = 1; j <= Limit; ++j)
			C[i][j] =
				(C[i - 1][j] + C[i - 1][j - 1]) % MOD;
	}
}

struct Unit {
	int Digit[LMT +5];

    int & operator [] (int Idx)
    {
		return Digit[Idx];
    }

    Unit(void) {
		Digit[0] = 1;
    }
};

struct Interval {
	int From, To, Size, Extra;
	bool IsRev;
	Unit Digit;

	void CalcSize(void)
	{
        Size = To - From + 1;
	}

	Interval(void) : IsRev(false), Extra(0), Digit() {}
} Tree[MAXN * 4];

Unit Merge(Interval x, Interval y)
{
    Unit Result;

    for (int i = 1; i <= LMT; ++i) {
        Result[i] = (x.Digit[i] + y.Digit[i]) % MOD;

        for (int j = 1; j < i; ++j) {
            int Temp =
				(long long)x.Digit[j] * y.Digit[i - j] % MOD;

            Result[i] = ((Result[i] + Temp) % MOD + MOD) % MOD;
        }
    }

    return Result;
}

void Build(int Crt, int From, int To)
{
	Tree[Crt].From = From;
	Tree[Crt].To = To;
	Tree[Crt].CalcSize();

    if (From == To) {
		int x;
		scanf("%d", &x);

        Tree[Crt].Digit[1] = (x % MOD + MOD) % MOD;
        return;
    }

    int Half = (From + To) / 2,
		Left = Crt * 2, Right = Left + 1;

    Build(Left, From, Half);
    Build(Right, Half + 1, To);
    Tree[Crt].Digit = Merge(Tree[Left], Tree[Right]);
}

void Turn(int Crt)
{
    Tree[Crt].IsRev ^= 1;

    if (Tree[Crt].Extra)
        Tree[Crt].Extra =
			(MOD - Tree[Crt].Extra % MOD) % MOD;

    for (int i = 1; i <= LMT; ++i)
		if ((i % 2 == 1) &&
			Tree[Crt].Digit[i])
			Tree[Crt].Digit[i] =
				(MOD - Tree[Crt].Digit[i] % MOD) % MOD;
}

void Change(int Crt, int Val)
{
    Tree[Crt].Extra =
		((Tree[Crt].Extra + Val) % MOD + MOD) % MOD;

	int Temp = Val;
    for (int i = LMT; i > 0; --i)
	{
        for (int j = i - 1; j > 0; --j) {
            Tree[Crt].Digit[i] = (
				(Tree[Crt].Digit[i] +
					(long long)Temp * Tree[Crt].Digit[j] % MOD *
					C[Tree[Crt].Size - j][i - j] % MOD) + MOD) % MOD;

            Temp = (long long)Temp * Val % MOD;
        }

        Tree[Crt].Digit[i] = (
			(Tree[Crt].Digit[i] +
				(long long)Temp *
				C[Tree[Crt].Size][i] % MOD) + MOD) % MOD;

		Temp = Val;
	}
}


void Down(int Crt)
{
    if (Tree[Crt].IsRev) {
        Turn(Crt * 2);
        Turn(Crt * 2 + 1);

        Tree[Crt].IsRev = false;
    }

    if (Tree[Crt].Extra) {
        Change(Crt * 2, Tree[Crt].Extra);
        Change(Crt * 2 + 1, Tree[Crt].Extra);

        Tree[Crt].Extra = 0;
    }
}


void Reverse(int Crt, int From, int To)
{
    int CrtFrom = Tree[Crt].From,
		CrtTo = Tree[Crt].To;

	if (From <= CrtFrom && To >= CrtTo) {
        Turn(Crt);

        return;
	}

    Down(Crt);

    int Half = (CrtFrom + CrtTo) / 2,
		Left = Crt * 2, Right = Left + 1;

	if (From <= Half) Reverse(Left, From, To);
	else if (To > Half) Reverse(Right, From, To);
    Tree[Crt].Digit = Merge(Tree[Left], Tree[Right]);
}



void Edit(int Crt, int From, int To, int Val)
{
    int CrtFrom = Tree[Crt].From,
		CrtTo = Tree[Crt].To;

	if (From <= CrtFrom && To >= CrtTo) {
        Change(Crt, Val);

        return;
	}

    Down(Crt);

    int Half = (CrtFrom + CrtTo) / 2,
		Left = Crt * 2, Right = Left + 1;

	if (From <= Half) Edit(Left, From, To, Val);
	else if (To > Half) Edit(Right, From, To, Val);
    Tree[Crt].Digit = Merge(Tree[Left], Tree[Right]);
}

Interval Qry(int Crt, int From, int To, int k)
{
	int CrtFrom = Tree[Crt].From,
		CrtTo = Tree[Crt].To;

	if (From == CrtFrom && To == CrtTo) {
        return Tree[Crt];
	}

    Down(Crt);

    int Half = (CrtFrom + CrtTo) / 2,
		Left = Crt * 2, Right = Left + 1;

	if (From <= Half) return Qry(Left, From, To, k);
	else if (To > Half) return Qry(Right, From, To, k);
    else {
		Interval x;
		x.Digit = Merge(Qry(Left, From, Half, k), Qry(Right, Half + 1, To, k));
		return x;
    }
}

struct Main {
	int m;

	Main(void)
	{
		scanf("%d %d", &n, &m);

		CalcC();

		Build(1, 1, n);

		while (m--) {
			int Type;
			scanf("%d", &Type);

            if (Type == 1) { // add
                int From, To, Val;
                scanf("%d %d %d", &From, &To, &Val);

                Val = (Val % MOD + MOD) % MOD;

                Edit(1, From, To, Val);
            } else if (Type == 2) { // reverse
                int From, To;
                scanf("%d %d", &From, &To);

                Reverse(1, From, To);
            } else { // calc
                int From, To, k;
                scanf("%d %d %d", &From, &To, &k);

                Interval x = Qry(1, From, To, k);

                printf("%d\n",
					x.Digit[k]);
            }
		}
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
#endif // LOCAL

	delete new Main();

	return 0;
}
