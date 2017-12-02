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
typedef long long INT;
int readIn()
{
	bool minus = false;
	int a = 0;
	int ch = getchar();
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
	if(minus) a = -a;
	return a;
}
bool readIn(char* str, int* l)
{
	bool minus = false;
	int& length = *l;
	length = 0;
	int ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		str[length++] = ch - '0';
		ch = getchar();
	}
	return minus;
}

const int maxn = 105;
int n, m;
bool minus[maxn];
int length[maxn];
const INT digit = 10;
char origin[maxn][10005];
const INT Prime[] =
{
	10007, //用于快速求值
	199999769 //用于准确判断
};
const int size = sizeof(Prime) / sizeof(INT);
INT A[size][maxn];

INT Mod(int index, INT mod)
{
	INT ret = 0;
	for (int i = 0; i < length[index]; i++)
	{
		ret *= digit;
		ret += origin[index][i];
		ret %= mod;
	}
	if (minus[index])
	{
		ret = -ret;
		ret += mod;
	}
	return ret % mod;
}

INT Polynomial(INT x, int modIndex)
{
	INT ret = A[modIndex][n];
	for (int i = n; i >= 1; i--)
	{
		ret *= x;
		ret %= Prime[modIndex];
		ret += A[modIndex][i - 1];
		ret %= Prime[modIndex];
	}
	return ret;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 0; i <= n; i++)
	{
		minus[i] = readIn(origin[i], &length[i]);
	}
	for (int i = 0; i < size; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			A[i][j] = Mod(j, Prime[i]);
		}
	}

	std::vector<bool> isAns(m + 1);
	std::vector<int> ans;
	for (int x = 1; x < Prime[0]; x++)
	{
		if (!Polynomial(x, 0))
		{
			for(int i = x; i <= m; i += Prime[0])
			{
				isAns[i] = true;
			}
		}
	}
	for (int x = 1; x <= m; x++)
	{
		if(isAns[x] && !Polynomial(x, 1))
		{
			ans.push_back(x);
		}
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++)
	{
		printf("%d\n", ans[i]);
	}
}

int main()
{
	run();
	return 0;
}
