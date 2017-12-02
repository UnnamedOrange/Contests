#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
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

INT rand(INT from, INT to)
{
	INT r = (rand() << 15) + rand();
	return r % (to - from + 1) + from;
}

void run()
{
	srand(time(NULL));
	INT n = 1005;
	printf("%d %d\r\n", n, rand(1, 100000000));
	for(int i = 1; i <= n - 1; i++)
	{
		INT p = rand(1, i);
		printf("%d %d\r\n", p, rand(1, 100000000));
	}
}

int main()
{
	freopen("data.in", "w", stdout);
	run();
	return 0;
}
