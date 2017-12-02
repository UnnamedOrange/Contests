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
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT maxn = 20;
INT n, m;
double x[maxn];
double y[maxn];
INT f[300000];

void run()
{
	INT t = readIn();
	while(t--)
	{
		n = readIn();
		m = readIn();

		for(int i = 0; i < n; i++)
		{
			scanf("%lf%lf", &x[i], &y[i]);
		}

		INT U = 1 << n;
		std::fill(f, f + U, n);
		f[0] = 0;
		for(int S = 1; S < U; S++)
		{
			INT s1 = 0;
			for(int i = 0; i < n; i++)
			{
				if(S & (1 << i)) s1 = i;
			}
			f[S] = std::min(f[S], f[S ^ (1 << s1)] + 1);

			for(int s2 = 0; s2 < s1; s2++)
			{
				if(!(S & (1 << s2))) continue;
				//解二元一次方程组
				//a * x[s1]^2 + b * x[s1] = y[s1]
				//a * x[s2]^2 + b * x[s2] = y[s2]
				double a =
				    (y[s1] * x[s2] - y[s2] * x[s1]) /
				    //----------------------------------
				    ((x[s1] * x[s2]) * (x[s1] - x[s2]));
				double b =
				    (y[s1] * x[s2] * x[s2] - y[s2] * x[s1] * x[s1]) /
				    //-----------------------------------------------
				    ((x[s1] * x[s2]) * (x[s2] - x[s1]));
				if(a >= 0)
				{
					f[S] = std::min(f[S], f[S ^ (1 << s2)] + 1);
					continue;
				}

				INT S0 = S ^ (1 << s1) ^ (1 << s2);
				for(int i = 0; i < s1; i++)
				{
					if(S0 & (1 << i) && a * x[i] * x[i] + b * x[i] == y[i])
					{
						S0 ^= (1 << i);
					}
				}
				f[S] = std::min(f[S], f[S0] + 1);
			}
		}
		cout << f[U - 1] << endl;
	}
}

int main()
{
	run();
	return 0;
}
