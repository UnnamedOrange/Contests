#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
#include <random>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

std::default_random_engine e;
using Rand = std::uniform_int_distribution<int>;
int rand(int l, int r)
{
	return Rand(l, r)(e);
}

void run()
{
	do
	{
		FILE* file = fopen("tree.in", "w");
		int n = 2000;
		int m = 2000;
		int threshold = n / 5 * 3;
		fprintf(file, "%d %d 0\n", n, m);
		for (int i = 2; i <= threshold; i++)
			fprintf(file, "%d %d %d\n", i - 1, i, rand(1, 1e4));
		for (int i = threshold + 1; i <= n; i++)
			fprintf(file, "%d %d %d\n", rand(1, i - 1), i, rand(1, 1e4));

		for (int i = 1; i <= m; i++)
		{
			if (rand(0, 1))
				fprintf(file, "modify %d %d\n", rand(1, n - 1), rand(1, 1e4));
			else
			{
				int r = rand(1, n);
				int l = rand(1, r);
				fprintf(file, "query %d %d %d\n", l, r, rand(1, n));
			}
		}
		fclose(file);

		printf("start\n");
		std::system("1.exe < tree.in > 1.out");
		std::system("2.exe < tree.in > 2.out");
	} while (!std::system("fc 1.out 2.out /n"));
}

int main()
{
	run();
	return 0;
}