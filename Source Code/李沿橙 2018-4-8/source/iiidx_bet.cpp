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
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar(' ');
}

const int maxn = int(5e5) + 5;
int n = 10;
double k = 2;
int a[maxn];

void run()
{
	for (int i = 1; i <= n; i++)
		a[i] = i;
	while (true)
	{
		std::random_shuffle(a + 1, a + 1 + n);
		k = (double)RAND_MAX / rand() + 0.1;

		FILE* file;
		file = fopen("iiidx.in", "w");
		fprintf(file, "%d %.1f\n", n, k);
		for (int i = 1; i <= n; i++)
			fprintf(file, "%d ", a[i]);
		fclose(file);

		system("1.exe < iiidx.in > 1.out");
		system("2.exe < iiidx.in > 2.out");
		if (system("fc 1.out 2.out"))
		{
			return;
		}
	};
}

int main()
{
	run();
	return 0;
}