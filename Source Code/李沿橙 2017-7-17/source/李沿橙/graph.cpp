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
inline INT readIn()
{
	bool minus = false;
	INT a = 0;
	char ch = getchar();
	while (!(ch >= '0' && ch <= '9')) ch = getchar();
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
	if (!x)
	{
		putchar('0');
		return;
	}
	bool minus = x < 0;
	if (minus) x = -x;
	char temp[20] = { 0 };
	int length = 0;
	while (x)
	{
		temp[length++] = x % 10 + '0';
		x /= 10;
	}
	if (minus)
	{
		temp[length++] = '-';
	}
	while (true)
	{
		putchar(temp[--length]);
		if (!length) return;
	}
}

const int maxn = 1e5 + 5;
int n;
INT k;
//±©Á¦±¶Ôö
int next[35][maxn];
INT length[35][maxn];
int minLen[35][maxn];

void run()
{
	n = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++)
	{
		next[0][i] = readIn() + 1;
	}
	for (int i = 1; i <= n; i++)
	{
		length[0][i] = minLen[0][i] = readIn();
	}

	int size = 0;
	while (1ll << size <= k) size++;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			next[i][j] = next[i - 1][next[i - 1][j]];
			length[i][j] = length[i - 1][j] + length[i - 1][next[i - 1][j]];
			minLen[i][j] = std::min(minLen[i - 1][j], minLen[i - 1][next[i - 1][j]]);
		}
	}

	for (int i = 1; i <= n; i++)
	{
		INT temp = k;
		INT lengthAns = 0;
		int minAns = 0x3fffffff;
		int cnt = i;
		for (int j = size; ~j; j--)
		{
			if (temp & (1ll << j))
			{
				lengthAns += length[j][cnt];
				minAns = std::min(minAns, minLen[j][cnt]);
				cnt = next[j][cnt];
			}
		}
		printOut(lengthAns);
		putchar(' ');
		printOut(minAns);
		putchar('\n');
	}
}

//2s
int main()
{
	run();
	return 0;
}