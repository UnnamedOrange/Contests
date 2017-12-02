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
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const int maxn = 200005;
int n;
int G[maxn];
bool vis[maxn];
std::vector<std::vector<int> > GT;
std::stack<int> sequeue;
int ans = -1;
int temp;

void dfsG(int from)
{
	if(vis[from]) return;
	vis[from] = true;
	dfsG(G[from]);
	sequeue.push(from);
}
void dfsGT(int from)
{
	if(vis[from]) return;
	vis[from] = true;
	temp++;
	for(int i = 0; i < GT[from].size(); i++)
	{
		dfsGT(GT[from][i]);
	}
}

void run()
{
	n = readIn();
	GT.resize(n + 1);
	for(int i = 1; i <= n; i++)
	{
		G[i] = readIn();
		GT[G[i]].push_back(i);
	}
	memset(vis, 0, sizeof(bool) * (n + 1));
	for(int i = 1; i <= n; i++)
	{
		if(!vis[i]) dfsG(i);
	}

	memset(vis, 0, sizeof(bool) * (n + 1));
	while(!sequeue.empty())
	{
		int top = sequeue.top();
		sequeue.pop();
		if(vis[top]) continue;

		temp = 0;
		dfsGT(top);
		if(temp > 1 && (ans == -1 || temp < ans))
		{
			ans = temp;
		}
	}
	printf("%d\n", ans);
}

int main()
{
	run();
	return 0;
}
