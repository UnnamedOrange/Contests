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

const int maxn = 200005;
const INT mod = 10007;
int n;
std::vector<std::vector<int> > edges;
INT weight[maxn];
INT maxAns;
INT sumAns;

void run()
{
	n = readIn();
	edges.resize(n + 1);
	for (int i = 2; i <= n; i++)
	{
		int from = readIn();
		int to = readIn();
		edges[from].push_back(to);
		edges[to].push_back(from);
	}
	for (int i = 1; i <= n; i++)
	{
		weight[i] = readIn();
	}

	for (int i = 1; i <= n; i++)
	{
		if (edges[i].size() < 2) continue;
		INT iMajor = 0;
		INT iMinor = 0;
		INT iSum = 0;
		for (int j = 0; j < edges[i].size(); j++)
		{
			if (weight[edges[i][j]] > iMinor)
			{
				if (weight[edges[i][j]] > iMajor)
				{
					iMinor = iMajor;
					iMajor = weight[edges[i][j]];
				}
				else
				{
					iMinor = weight[edges[i][j]];
				}
			}

			iSum += weight[edges[i][j]];
			iSum %= mod;
		}
		maxAns = std::max(maxAns, iMajor * iMinor);
		for (int j = 0; j < edges[i].size(); j++)
		{
			sumAns += (iSum + mod - weight[edges[i][j]]) % mod * weight[edges[i][j]] % mod;
			sumAns %= mod;
		}
	}
	cout << maxAns << " " << sumAns << endl;
}

int main()
{
	run();
	return 0;
}
