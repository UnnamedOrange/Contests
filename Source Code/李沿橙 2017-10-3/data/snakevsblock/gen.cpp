#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int n, m;
int rnd()
{
	return (rand() << 15) + rand();
}
long long rndLL()
{
	return ((1LL * rnd()) << 30) + rnd();
}
long long get_rand_num(long long range)
{
	if (range < 100000000000000LL)
	{  // 1e14
		return rndLL() % range;
	}
	else
	{
		long long tmp = range >> 32;
		return (((rndLL() % (tmp + 1)) << 32) + rndLL() % (1LL << 32)) % range;
	}
}
bool flag[205][5];
int x, y;
int main()
{
	srand(GetTickCount());
	n = 200;
	m = get_rand_num(n + 1);
	int mid = get_rand_num(n) + 1;
	printf("%d\n", n);
	for (int i = 1; i <= n; i++, puts(""))
	{
		if (i <= mid)
			for (int j = 1; j <= 5; j++)
				printf("%d ", ((i == 1 && j == 3) || rnd() & 3)? 0 : (rnd() & 1? get_rand_num(10) + 1 : get_rand_num(5) + 1));
		else
			for (int j = 1; j <= 5; j++)
				printf("%d ", rnd() & 3? 0 : (rnd() & 1? -get_rand_num(10) - 1 : -get_rand_num(5) - 1));
	}
	printf("%d\n", m);
	for (int i = 1; i <= m; i++)
	{
		do
			x = get_rand_num(n) + 1, y = get_rand_num(4) + 1;
		while (flag[x][y]);
		flag[x][y] = true;
		printf("%d %d\n", x, y);
	}
	return 0;
}