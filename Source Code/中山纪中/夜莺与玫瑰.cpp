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
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline void printOut(INT x)
{
	if(!x)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	char buffer[12];
	INT length = 0;
	while(x)
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	do
	{
		putchar(buffer[--length]);
	}while(length);
	putchar('\n');
}

const INT mod = 1 << 30;
INT T;
INT n, m;
INT Phi[4005];
INT phi(INT x)
{
	if(Phi[x]) return Phi[x];
	INT& ans = Phi[x];
	ans = x;
	INT to = sqrt(x);
	for(int i = 2; i <= to; i++)
	{
		if(x % i) continue;
		ans /= i;
		ans *= i - 1;
		while(!(x % i)) x /= i;
	}
	if(x != 1)
	{
		ans /= x;
		ans *= x - 1;
	}
	return ans;
}
INT gcd(INT x, INT y)
{
	if(!y) return x;
	return gcd(y, x % y);
}

#define RunInstance(x) delete new x()
struct work
{
	INT mem[4005][4005];
	INT getLine(INT width, INT height)
	{
		if(mem[width][height]) return mem[width][height];
		INT& ret = mem[width][height];
		ret = width / height * phi(height);
		INT pre = width / height * height + 1  ;
		for(int i = 1; pre <= width; i++, pre++)
		{
			ret += (gcd(i, height) == 1);
		}
		return ret;
	}
	
	work() : mem()
	{
		while(T--)
		{
			n = readIn();
			m = readIn();
			INT ans = 0;
			for(int y = 0; y < m; y++)
			{
				for(int i = 1; i <= n - 1; i++)
				{
					ans += (getLine(y, i) + getLine(m - y - 1, i)) * (n - i) % mod;
				}
			}
			ans += (n - 1) * m + (m - 1) * n;
			ans %= mod;
			printOut(ans);
		}
	}
};
struct cheat
{

};
void run()
{
	T = readIn();
	RunInstance(work);
}

int main()
{
	run();
	return 0;
}
