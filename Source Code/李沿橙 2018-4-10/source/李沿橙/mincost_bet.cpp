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
#include <windows.h>
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
	putchar('\n');
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1)));
const int maxn = int(3e5) + 5;
const int maxm = int(5e5) + 5;
int n = 4000;
int m;
int k;
int a[maxn];
int b[maxn];
bool map[5005][5005];
void genMap()
{
	m = 0;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
			if(map[i][j] = (rand() >= 32755))
//			if(map[i][j] = (rand() >= 15000))
				m++;
}
void genWeight()
{
	k = rand() % n + 1;
	for(int i = 1; i <= n; i++)
	{
		a[i] = rand() + 1;
		b[i] = rand() + 1;
	}
}

void run()
{
	srand(time(NULL) + clock());
	LL stamp;
	while(true)
	{
		puts("generating data...");
		stamp = clock();
		genWeight();
		genMap();
		FILE* input = fopen("mincost.in", "w");
		fprintf(input, "%d %d %d\n", n, m, k);
		for(int i = 1; i <= n; i++)
			fprintf(input, "%d %d\n", a[i], b[i]);
		for(int i = 1; i <= n; i++)
			for(int j = i + 1; j <= n; j++)
				if(map[i][j])
					fprintf(input, "%d %d\n", i, j);
		fclose(input);
		printf("generated in %d ms\n", clock() - stamp);
		
		puts("running 1");
		stamp = clock();
		system("1.exe < mincost.in > 1.out");
		printf("run in %d ms\n", clock() - stamp);
		
		puts("running 2");
		stamp = clock();
		system("2.exe < mincost.in > 2.out");
		printf("run in %d ms\n", clock() - stamp);
		
		if(system("fc 1.out 2.out /l"))
		{
			system("pause > nul");
			break;
		}
		Sleep(200);
		system("cls");
	}
}

int main()
{
	run();
	return 0;
}
