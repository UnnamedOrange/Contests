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
typedef int INT;
inline INT readIn()
{
	bool minus = false;
	INT a = 0;
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

const int maxn = 10005;
int n, m, k;
INT X[maxn];
INT Y[maxn];
struct pipe
{
	INT P;
	INT L;
	INT H;

	bool operator< (const pipe& b) const
	{
		return P < b.P;
	}
} pipes[maxn];

INT minClick = 0x7fffffff;
INT maxThrough;
bool bWin;

INT pipeIndex;
INT click;
void dfs(int h, int x = 1)
{
	if (click > minClick) return;
	if (x == n + 1)
	{
		minClick = std::min(minClick, click);
		bWin = true;
		return;
	}
	bool onPipe = false;
	INT maxH = m;
	INT minH = 0;
	if (pipeIndex < k && pipes[pipeIndex].P == x)
	{
		onPipe = true;
		maxH = pipes[pipeIndex].H;
		minH = pipes[pipeIndex].L;
		pipeIndex++;
	}
	if (h - Y[x] > minH && h - Y[x] < maxH)
	{
		if (onPipe) maxThrough = std::max(pipeIndex, maxThrough);
		dfs(h - Y[x], x + 1);
	}
	for (int i = X[x], j = 1; h + i - X[x] < m; i += X[x], j++)
	{
		int next = std::min(m, h + i);
		if (next > minH && (!onPipe || next < maxH))
		{
			click += j;
			if (onPipe) maxThrough = std::max(pipeIndex, maxThrough);
			dfs(next, x + 1);
			click -= j;
		}
	}
	if (onPipe) pipeIndex--;
}

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= n; i++)
	{
		X[i] = readIn();
		Y[i] = readIn();
	}
	for (int i = 0; i < k; i++)
	{
		pipes[i].P = readIn();
		pipes[i].L = readIn();
		pipes[i].H = readIn();
	}
	std::sort(pipes, pipes + k);

	for (int i = m; i >= 1; i--)
		dfs(i);
	if (bWin)
		cout << 1 << endl << minClick << endl;
	else
		cout << 0 << endl << maxThrough << endl;
}

int main()
{
	run();
	return 0;
}