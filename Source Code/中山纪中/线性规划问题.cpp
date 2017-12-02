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
typedef int INT;
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

const INT maxn = 1005;
INT n, P;
INT A[maxn], B[maxn], C[maxn];

void run()
{
	INT a = readIn();
	while(a--)
	{
		n = readIn();
		P = readIn();
		
		for(int i = 0; i < n; i++)
		{
			A[i] = readIn();
		}
		for(int i = 0; i < n; i++)
		{
			B[i] = readIn();
		}
		for(int i = 0; i < n; i++)
		{
			C[i] = readIn();
		}
		
		INT ans = -1;
		INT U = (1 << n) - 1;
		for(int i = 0; i <= U; i++)
		{
			INT sumA = 0;
			INT sumB = 0;
			INT sumC = 0;
			for(int j = 0; j < n; j++)
			{
				if(i & (1 << j))
				{
					sumA += A[j];
					sumB += B[j];
					sumC += C[j];
				}
			}
			if(sumA <= P && sumB >= P && (ans == -1 || sumC < ans))
			{
				ans = sumC;
			}
		}
		if(~ans)
		{
			cout << ans << endl;
		}
		else
		{
			cout << "IMPOSSIBLE!!!" << endl;
		}
	}
}

int main()
{
	run();
	return 0;
}
