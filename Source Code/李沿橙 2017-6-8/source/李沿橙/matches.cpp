#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
inline int readIn(int a = 0)
{
	scanf("%d",&a);
	return a;
}

int n;
const int table[]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 8, 9, 6, 9, 29, 39, 38, 65, 88, 128};

namespace Regular
{
	void run()
	{
		printf("%d\n",table[n]);
	}
	void input()
	{
		n=readIn();
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
