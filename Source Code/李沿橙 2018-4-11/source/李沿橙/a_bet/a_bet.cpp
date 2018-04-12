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
typedef LL INT_PUT;
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
	putchar('\n');
}

int n = 2000;

void generate()
{
	FILE* file = fopen("a.in", "w");
	fprintf(file, "%d\n", n);
	int param = rand();
	for (int i = 1; i <= n; i++)
		fprintf(file, "%d", rand() >= param);
	fclose(file);
}

void run1()
{
	system("1.exe < a.in > 1.out");
}

void run2()
{
	system("2.exe < a.in > 2.out");
}

bool check()
{
	return system("fc 1.out 2.out /n");
}

void run()
{
	srand(time(NULL) + clock());
	while (true)
	{
		int stamp;

		puts("generating data...");
		stamp = clock();
		generate();
		printf("generated in %d ms\n", clock() - stamp);

		puts("running 1...");
		stamp = clock();
		run1();
		printf("run in %d ms\n", clock() - stamp);

		puts("running 2...");
		stamp = clock();
		run2();
		printf("run in %d ms\n", clock() - stamp);

		if (check())
		{
			system("pause > nul");
			break;
		}
	}
}

int main()
{
	run();
	return 0;
}