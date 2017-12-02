#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int n, k;
char s[1000005];
int rnd()
{
	return (rand() << 15) + rand();
}
long long rndLL()
{
	return ((1LL * rnd()) << 30) + rnd();
}
char get_rand_char()
{
	if (rnd() & 1) return rnd() & 1? '2' : '3';
	else return rnd() % 10 + '0';
}
long long gen_rand_num(long long range)
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
int main()
{
	srand(GetTickCount());
	for (int i = 1; i <= 10; i++)
	{
		n = gen_rand_num(1000000);
		k = rnd() & 1? gen_rand_num(n / 2) : gen_rand_num(1000000000);
		printf("%d %d\n", n, k);
		for (int j = 0; j < n; j++)
			do
				s[j] = get_rand_char();
			//while (j > 0 && s[j - 1] == '2' && s[j] == '3');
			while (j > 1 && s[j - 2] == '2' && (s[j - 1] == '2' || s[j - 1] == '3') && s[j] == '3' && (rnd() & 16383));
		s[n] = '\0';
		puts(s);
	}
	return 0;
}