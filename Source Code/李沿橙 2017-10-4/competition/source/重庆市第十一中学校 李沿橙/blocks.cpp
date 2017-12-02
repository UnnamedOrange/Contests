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

const INT INF = (~(INT(1) << (sizeof(INT) * 8 - 1)));
const INT maxn = 1000005;
INT n, m, K;
INT a[maxn];

#define RunInstance(x) delete new x
struct work
{
	struct Node
	{
		INT l;
		INT r;
		INT remain;
		Node() {}
		Node(INT l, INT r, INT remain) : l(l), r(r), remain(remain) {}
		bool operator== (const Node& b) const
		{
			return l == b.l && r == b.r && remain == b.remain;
		}
	} emp;

	std::vector<Node> nodes;
	std::vector<INT> sum;

	INT ans;

	void getNodes()
	{
		INT sum = 0;
		INT l = -1;
		for(int i = 1; i <= n; i++)
		{
			if(a[i] >= K)
			{
				if(l == -1)
				{
					l = i;
					sum = a[i] - K;
				}
				else
				{
					sum += a[i] - K;
				}
			}
			else
			{
				if(l != -1)
				{
					nodes.push_back(Node(l, i - 1, sum));
					ans = std::max(ans, nodes.back().r - nodes.back().l + 1);
					l = -1;
				}
			}
		}
		if(l != -1)
		{
			nodes.push_back(Node(l, n, sum));
			ans = std::max(ans, nodes.back().r - nodes.back().l + 1);
		}
	}
	void getSum()
	{
		for(int i = 1; i <= n; i++)
		{
			sum[i] = sum[i - 1] + a[i];
		}
	}

	bool expandNode(Node& cnt, const Node& r)
	{
		if(cnt == emp)
		{
			cnt = r;
			return true;
		}
		INT allCollected = cnt.remain + r.remain;
		INT needExpand = (K * (r.l - cnt.r - 1)) - (sum[r.l - 1] - sum[cnt.r]);
		if(allCollected < needExpand) return false;
		cnt = Node(cnt.l, r.r, allCollected - needExpand);
		return true;
	}
	INT expandTwoSide(const Node& cnt)
	{
		INT l = cnt.l, r = cnt.r;
		INT remain = cnt.remain;
		while(l > 1 && a[l - 1] < K && remain - (K - a[l - 1]) >= 0)
		{
			remain -= K - a[l - 1];
			l--;
		}
		INT ret = r - l + 1;
		while(l <= cnt.l)
		{
			while(r < n && a[r + 1] < K && remain - (K - a[r + 1]) >= 0)
			{
				remain -= K - a[r + 1];
				r++;
			}
			ret = std::max(ret, r - l + 1);

			remain += K - a[l];
			l++;
		}
		return ret;
	}
	void cutNode(Node& cnt, Node& l, Node& next)
	{
		if(cnt == l)
		{
			cnt = emp;
			return;
		}
		INT allCollected = cnt.remain - l.remain;
		INT needExpand = (K * (next.l - l.r - 1)) - (sum[next.l - 1] - sum[l.r]);
		cnt = Node(next.l, cnt.r, allCollected + needExpand);
	}

	work() : ans(), sum(n + 1), emp(0, 0, 0)
	{
		getNodes();
		if(!nodes.size())
		{
			cout << 0 << " ";
			return;
		}

		getSum();
		Node cnt = emp;
		INT r = 0;
		for(int l = 0; l < nodes.size(); l++)
		{
			while(r < nodes.size() && expandNode(cnt, nodes[r]))
			{
				ans = std::max(ans, cnt.r - cnt.l + 1);
				ans = std::max(ans, expandTwoSide(cnt));
				r++;
			}

			if(l != nodes.size() - 1) cutNode(cnt, nodes[l], nodes[l + 1]);
		}

		cout << ans << " ";
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= n; i++)
	{
		a[i] = readIn();
	}
	while(m--)
	{
		K = readIn();
		RunInstance(work);
	}
}

int main()
{
#ifndef JUDGE
	freopen("blocks.in", "r", stdin);
	freopen("blocks.out", "w", stdout);
#endif
	run();
	return 0;
}
