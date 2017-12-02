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
const int root = 1;
int n;
std::vector<std::vector<int> > edges;
INT weight[maxn];
INT parent[maxn];
INT grand[maxn];
INT fMax[maxn]; //���ӽ������Ȩֵ
INT fSum[maxn]; //���ӽ��Ȩֵ֮��
INT fCSum[maxn]; //�ӽ��Ȩֵ֮��
INT fCMajor[maxn]; //�ӽ�����Ȩֵ
INT fCMinor[maxn]; //�ӽ��δ�Ȩֵ
INT maxAns;
INT sumAns;

void dfs(int node = root)
{
	if (parent[node]) //���¸��ڵ�
	{
		fCSum[parent[node]] += weight[node];
		fCSum[parent[node]] %= mod;
		if (weight[node] > fCMinor[parent[node]])
		{
			if (weight[node] > fCMajor[parent[node]])
			{
				fCMinor[parent[node]] = fCMajor[parent[node]];
				fCMajor[parent[node]] = weight[node];
			}
			else
			{
				fCMinor[parent[node]] = weight[node];
			}
		}
	}
	if (grand[node]) //����ү�ڵ�
	{
		fMax[grand[node]] = std::max(fMax[grand[node]], weight[node]);
		fSum[grand[node]] += weight[node];
		fSum[grand[node]] %= mod;
	}

	for (int i = 0; i < edges[node].size(); i++)
	{
		int& to = edges[node][i];
		if (to == parent[node]) continue;
		parent[to] = node;
		if (parent[node]) grand[to] = parent[node];
		dfs(to);
	}
	//�����������
	maxAns = std::max(maxAns, fMax[node] * weight[node]);
	sumAns += fSum[node] % mod * weight[node] % mod * 2; //��ס����2
	sumAns %= mod;

	//����ͬ����
	if (edges[node].size() - bool(parent[node]) >= 2) //��Ҫ������2���ӽ��
	{
		INT& sum = fCSum[node];
		maxAns = std::max(maxAns, fCMajor[node] * fCMinor[node]);
		for (int i = 0; i < edges[node].size(); i++)
		{
			int& to = edges[node][i];
			if (to == parent[node]) continue;
			sumAns += (sum + mod - weight[to]) % mod * weight[to] % mod; //���ﲻ����2
			sumAns %= mod;
		}
	}
}

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

	dfs();
	sumAns %= mod;
	cout << maxAns << " " << sumAns << endl;
}

int main()
{
	run();
	return 0;
}