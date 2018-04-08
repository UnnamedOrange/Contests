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
}

int rand(int l, int r)
{
	int ret = (rand() << 15) | rand();
	return l + ret % (r - l + 1);
}
int n, k;

void run()
{
	srand(time(NULL) + clock());
	n = 50;
	k = rand(1, n);
	printf("%d %d\n", n, k);
	int chain = n * 6 / 10;
	for (int i = 1; i < chain; i++)
		printf("%d ", i - 1);
	for (int i = chain; i < n; i++)
		printf("%d ", rand(0, i - 1));
}

int main()
{
	freopen("build.in", "w", stdout);
	run();
	return 0;
}