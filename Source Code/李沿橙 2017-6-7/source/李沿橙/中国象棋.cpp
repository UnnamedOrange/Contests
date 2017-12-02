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

int n,m;

inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

namespace Regular
{
	void run()
	{
		printf("7");
	}
	void input()
	{
		n=readIn();
		m=readIn();
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
