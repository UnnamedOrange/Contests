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
		a0 = readIn();
		a1 = readIn();
		b0 = readIn();
		b1 = readIn();

		//∵lcm(x,b0) == b1
		//∴x*b0/gcd(x,b0) == b1
		//∴x == gcd(x,b0)*b1/b0
		//∵gcd(x,b0)|b0
		//枚举b0的所有因数，时间复杂度为O(b0^(1/2))，另一个较大的因数为b0除以较小的因数
		//最后带入验证gcd(x,a0) == a1, lcm(x,b0) == b1
		//注意因数的判重 

		int ans = 0;
		int base = b1 / b0;
		int B0 = b0;
		int to = sqrt(b0);
		for (int i = 1; i <= to; i++)
		{
			if (b0 % i) continue;
			int x = base*i;
			if (gcd(x, a0) == a1 && x / gcd(x, b0)*b0 == b1)
				ans++;
			if (base*(b0 / i) != x) //注意因数的判重：忘记了就只有60分 
			{
				x = base*(b0 / i);
				if (gcd(x, a0) == a1 && x / gcd(x, b0)*b0 == b1)
					ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}