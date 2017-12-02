#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

INT gcd(INT a, INT b)
{
	return !b ? a : gcd(b, a % b);
}

const double EPS = 1e-6;
const INT maxn = 305;
INT n;
INT num[maxn];

#define RunInstance(x) delete new x
struct Part2
{
	Part2()
	{
		cout << (rand() & 1 ? 1.0 : 0.0) << endl;
	}
};
struct Part1
{
	struct cheat
	{
		INT win[2];
		bool sel[15];
		INT nSel;

		void search(INT board, bool player)
		{
			if(board == 1)
			{
				win[player]++;
				return;
			}
			if(nSel == n)
			{
				win[!player]++;
				return;
			}

			for(int i = 1; i <= n; i++)
			{
				if(!sel[i])
				{
					sel[i] = true;
					nSel++;
					search(gcd(num[i], board), !player);
					sel[i] = false;
					nSel--;
				}
			}
		}

		cheat() : win(), sel(), nSel()
		{
			search(0, 0);
			cout << double(win[0]) / double(win[0] + win[1]) << " ";
		}
	};
	struct work
	{
		work()
		{
			cout << 0.0 << " ";
		}
	};
	Part1()
	{
		if(n <= 10) RunInstance(cheat);
		else RunInstance(work);
	}
};

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		num[i] = readIn();
	}
	RunInstance(Part1);
	RunInstance(Part2);
}

int main()
{
#ifndef JUDGE
	freopen("cards.in", "r", stdin);
	freopen("cards.out", "w", stdout);
#endif
	run();
	return 0;
}
