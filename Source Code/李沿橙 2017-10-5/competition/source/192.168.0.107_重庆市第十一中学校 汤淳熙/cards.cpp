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

/*

n 张纸牌（有一个正整数）

黑板
	开始为 0
	秀秀先手
	华华轮流

	选定一张牌，将黑板数字改写为 Gcd，然后弃置
	当数字为 1 或没有牌时时，就输了

随机策略获胜概率
最优策略获胜概率

 */

inline Gcd(int x, int y)
{
	return y == 0 ? x : Gcd(y, x % y);
}

struct Brute {
	int n;

	struct Heap {
		int Card[MAXN];

		int & operator [] (int Idx)
		{
			return Card[Idx];
		}
	} Ogl;

	enum { A, B };

	inline void Proc_1(void)
	{

		printf("%lf\n", 1.0);
	}

	inline void Proc_2(void)
	{
		printf("%lf\n", 1.0);
	}

	Brute(void)
	{
		scanf("%d", &n);

		for (int i = 1; i <= n; ++i)
			scanf("%d", Ogl.Card + i);

		Proc_1();

		Proc_2();
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("cards.in", "r", stdin);
	freopen("cards.out", "w", stdout);
#endif // LOCAL

	delete new Brute();

	return 0;
}
