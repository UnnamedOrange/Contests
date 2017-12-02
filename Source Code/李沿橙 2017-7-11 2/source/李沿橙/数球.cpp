#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

int n;

void run()
{
	n = readIn();
	int times = (n + 1) / 2;
	printf("%d\n", times);
	for(int i = 1; i <= times; i++)
	{
		printf("%d ", i);
		bool bPrint = false;
		for(int j = 1, k = i; j <= i; j++, k++)
		{
			printf("%s%d", bPrint ? " " : "", k);
			bPrint = true;
		}
		puts("");
	}
}

int main()
{
	run();
	return 0;
}
