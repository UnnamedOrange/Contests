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
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

int n;
int a0, a1, b0, b1;

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a%b);
}

int main()
{
	n = readIn();
	while (n--)
	{
		int ans = 0;
		a0 = readIn();
		a1 = readIn();
		b0 = readIn();
		b1 = readIn();

		for (int x = a1; x <= b1; x += a1)
		{
			if (gcd(a0, x) == a1 && b0 / gcd(b0, x)*x == b1) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}