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
int x, y, to[100005];
int main()
{
	srand(GetTickCount());
	n = 10;
	for (int i = 1; i <= n; i++) to[i] = i;
	random_shuffle(to + 1, to + n + 1);
	printf("%d %d\n", n, n - 1);
	for (int i = 1; i < n; i++) printf("%d %d\n", to[get_rand_num(i) + 1], to[i + 1]);
	m = /*get_rand_num(3) + 1;*/4;
	printf("%d\n", m);
	for (int i = 1; i <= m; i++) printf("%d %d\n", to[get_rand_num(n) + 1], to[get_rand_num(n) + 1]);
	return 0;
}