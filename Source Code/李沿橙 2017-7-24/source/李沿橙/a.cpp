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
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

void run()
{
	INT a = readIn();
	while(a--)
	{
		INT n = readIn();
		cout << n + 1 << endl;
	}
}

int main()
{
	run();
	return 0;
}
