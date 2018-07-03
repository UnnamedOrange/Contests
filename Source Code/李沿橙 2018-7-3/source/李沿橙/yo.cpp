#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
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
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

struct Vector
{
	double x, y;
	Vector() {}
	Vector(const double& x, const double& y) : x(x), y(y) {}
	void read()
	{
		x = readIn() * 10;
		y = readIn() * 10;
	}
};
typedef Vector Point;
int dcmp(const double& x)
{
	const double EPS = 1e-7;
	if (std::abs(x) <= EPS)
		return 0;
	return x < 0 ? -1 : 1;
}
Vector operator-(const Vector& a, const Vector& b)
{
	return Vector(a.x - b.x, a.y - b.y);
}
double Dot(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y;
}
double Length(const Vector& v)
{
	return std::sqrt(Dot(v, v));
}
double Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}

const int INF = (~(int(1) << (sizeof(int) * 8 - 1))) >> 1;
const int maxn = int(2e5) + 5;
int n, m;
Point points[maxn];
struct Station
{
	Vector vec;
	int c;
	void read()
	{
		vec.read();
		c = readIn();
	}
} stations[maxn];
struct Object
{
	int type;
	int idx;
	Vector vec;
	Object() {}
	Object(const Station& s, int idx) : type(1), idx(idx), vec(s.vec) {}
	Object(const Point& p, int idx) : type(2), idx(idx), vec(p) {}
	bool operator<(const Object& b) const
	{
		return dcmp(std::atan2(vec.y, vec.x) - std::atan2(b.vec.y, b.vec.x)) < 0;
	}
};
std::vector<Object> objects;
int neighbor[maxn][2];

#define RunInstance(x) delete new x
struct brute
{
	struct NetworkFlow
	{
		struct Edge
		{
			int from, to, cap, flow;
			Edge() {}
			Edge(int from, int to, int cap) : flow(), from(from), to(to), cap(cap) {}
		};
		std::vector<Edge> edges;
		std::vector<std::vector<int> > G;
		int s, t;
		int addEdge(int from, int to, int cap)
		{
			edges.push_back(Edge(from, to, cap));
			edges.push_back(Edge(to, from, 0));
			int i = edges.size();
			G[from].push_back(i - 2);
			G[to].push_back(i - 1);
			return i - 2;
		}

		int level[maxn * 3];
		std::vector<int> cur;
		int Dinic(int node, int opt)
		{
			if (node == t || !opt)
				return opt;
			int flow = 0;
			for (int& i = cur[node]; i < G[node].size(); i++)
			{
				Edge& e = edges[G[node][i]];
				int t;
				if (e.flow < e.cap && level[node] + 1 == level[e.to] && (t = Dinic(e.to, std::min(opt, e.cap - e.flow))))
				{
					flow += t;
					opt -= t;
					e.flow += t;
					edges[G[node][i] ^ 1].flow -= t;
					if (!opt) break;
				}
			}
			return flow;
		}

		struct Queue
		{
			int c[maxn * 3];
			int head, tail;
			Queue() : head(), tail() {}
			void clear() { head = tail = 0; }
			bool empty() { return head == tail; }
			void push(int x) { c[tail++] = x; }
			void pop() { head++; }
			int front() { return c[head]; }
		} q;
		int stamp;
		int vis[maxn * 3];
		bool BFS()
		{
			q.clear();
			level[s] = 0;
			stamp++;
			vis[s] = stamp;
			q.push(s);
			while (!q.empty())
			{
				int from = q.front();
				q.pop();
				for (int i = 0; i < G[from].size(); i++)
				{
					const Edge& e = edges[G[from][i]];
					if (e.flow < e.cap && vis[e.to] != stamp)
					{
						level[e.to] = level[e.from] + 1;
						vis[e.to] = stamp;
						q.push(e.to);
					}
				}
			}
			return vis[t] == stamp;
		}

		int maxFlow()
		{
			stamp = 0;
			std::memset(vis, 0, sizeof(vis));
			int flow = 0;
			while (BFS())
			{
				cur.clear();
				cur.resize(G.size());
				flow += Dinic(s, INF);
			}
			return flow;
		}
	} nf;

	int edge[maxn][2];

	brute()
	{
		nf.G.resize(n + m + 2);
		nf.s = n + m;
		nf.t = n + m + 1;
		for (int i = 0; i < n; i++)
		{
			edge[i][0] = nf.addEdge(i, n + neighbor[i][0], 1);
			if (~neighbor[i][1])
				edge[i][1] = nf.addEdge(i, n + neighbor[i][1], 1);
			else
				edge[i][1] = -1;
		}
		for (int i = 0; i < n; i++)
			nf.addEdge(nf.s, i, 1);
		for (int i = 0; i < m; i++)
			nf.addEdge(n + i, nf.t, stations[i].c);
		printOut(nf.maxFlow());
		putchar('\n');
		for (int i = 0; i < n; i++)
		{
			if (nf.edges[edge[i][0]].flow)
			{
				printOut(i);
				putchar(' ');
				printOut(nf.edges[edge[i][0]].to - n);
				putchar('\n');
			}
			else if (~edge[i][1] && nf.edges[edge[i][1]].flow)
			{
				printOut(i);
				putchar(' ');
				printOut(nf.edges[edge[i][1]].to - n);
				putchar('\n');
			}
		}
	}
};
struct work
{
	std::vector<std::pair<int, int> > ans;

	int idx[maxn];
	int count[maxn];
	struct NewObject
	{
		int type;
		int idx;
		int next;
		NewObject() {}
		NewObject(int type, int idx) : type(type), idx(idx) {}
		NewObject(const Object& obj) : type(obj.type), idx(obj.idx) {}
	};
	std::vector<NewObject> nobjects;

	int remain[maxn];
	int GetVal(int pos, int val)
	{
		for (int i = 0; i < m; i++)
			remain[i] = stations[i].c;
		int ret = 0;
		int pre = -1;
		for (int i = 1; i < nobjects.size(); i++)
		{
			if (nobjects[i].type == 1)
			{
				pre = nobjects[i].idx;
			}
			else
			{
				if (!~pre && val && remain[pos])
				{
					val--;
					ret++;
					remain[pos]--;
				}
				else
				{
					if (~pre && remain[pre])
					{
						ret++;
						remain[pre]--;
					}
					else if (remain[nobjects[i].next])
					{
						ret++;
						remain[nobjects[i].next]--;
					}
					else
					{
						int a = 0;
					}
				}
			}
		}
		return ret;
	}
	void MakeAns(int pos, int val)
	{
		for (int i = 0; i < m; i++)
			remain[i] = stations[i].c;
		int ret = 0;
		int pre = -1;
		for (int i = 1; i < nobjects.size(); i++)
		{
			if (nobjects[i].type == 1)
			{
				pre = nobjects[i].idx;
			}
			else
			{
				if (!~pre && val && remain[pos])
				{
					val--;
					ans.push_back(std::make_pair(nobjects[i].idx, pos));
					remain[pos]--;
				}
				else
				{
					if (~pre && remain[pre])
					{
						ans.push_back(std::make_pair(nobjects[i].idx, pre));
						remain[pre]--;
					}
					else if (remain[nobjects[i].next])
					{
						ans.push_back(std::make_pair(nobjects[i].idx, nobjects[i].next));
						remain[nobjects[i].next]--;
					}
				}
			}
		}
	}

	work() : count()
	{
		for (int i = 0; i < n; i++)
			if (!~neighbor[i][1])
				if (int& t = stations[neighbor[i][0]].c)
				{
					t--;
					ans.push_back(std::make_pair(i, neighbor[i][0]));
				}

		objects.resize(objects.size() >> 1);
		// assert(m >= 2);
		int cnt = -1;
		for (int i = 0; i < objects.size(); i++)
		{
			const Object& obj = objects[i];
			if (obj.type == 1)
			{
				idx[obj.idx] = i;
				cnt = obj.idx;
			}
			else if (obj.type == 2)
			{
				if (!~neighbor[obj.idx][1])
					continue;
				if (~cnt)
					count[cnt]++;
			}
		}
		for (int i = 0; i < objects.size() && objects[i].type != 1; i++)
			count[cnt]++;

		int minPos = std::min_element(count, count + m) - count;
		{
			int pos = 0;
			for (int i = 0; i < objects.size(); i++)
				if (objects[i].type == 1 && objects[i].idx == minPos)
				{
					pos = i;
					break;
				}
			for (int i = pos; i < objects.size(); i++)
				if (!(objects[i].type == 2 && !~neighbor[objects[i].idx][1]))
					nobjects.push_back(objects[i]);
			for (int i = 0; i < pos; i++)
				if (!(objects[i].type == 2 && !~neighbor[objects[i].idx][1]))
					nobjects.push_back(objects[i]);
			int next = nobjects[0].idx;
			for (int i = nobjects.size() - 1; ~i; i--)
				if (nobjects[i].type == 1)
					next = nobjects[i].idx;
				else if (nobjects[i].type == 2)
					nobjects[i].next = next;
		}

		int maxVal = 0;
		int maxIdx = 0;
		for (int i = 0; i <= count[minPos]; i++)
		{
			int t;
			if ((t = GetVal(minPos, i)) > maxVal)
			{
				maxVal = t;
				maxIdx = i;
			}
		}
		MakeAns(minPos, maxIdx);

		printOut(ans.size());
		putchar('\n');
		for (int i = 0; i < ans.size(); i++)
		{
			printOut(ans[i].first);
			putchar(' ');
			printOut(ans[i].second);
			putchar('\n');
		}
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 0; i < n; i++)
		points[i].read();
	for (int i = 0; i < m; i++)
		stations[i].read();

	for (int i = 0; i < n; i++)
		objects.push_back(Object(points[i], i));
	for (int i = 0; i < m; i++)
		objects.push_back(Object(stations[i], i));
	std::sort(objects.begin(), objects.end());
	for (int i = 0, to = objects.size(); i < to; i++)
		objects.push_back(objects[i]);

	int pre;
	pre = -1;
	for (int i = 0; i < objects.size(); i++)
	{
		const Object& obj = objects[i];
		if (obj.type == 1)
			pre = obj.idx;
		else if (obj.type == 2)
			if (~pre)
				neighbor[obj.idx][0] = pre;
	}
	pre = -1;
	for (int i = objects.size() - 1; ~i; i--)
	{
		const Object& obj = objects[i];
		if (obj.type == 1)
			pre = obj.idx;
		else if (obj.type == 2)
			if (~pre)
				neighbor[obj.idx][1] = pre;
	}

	for (int i = 0; i < n; i++)
	{
		if (neighbor[i][0] == neighbor[i][1])
			neighbor[i][1] = -1;
		else
		{
			const Vector& vec1 = stations[neighbor[i][0]].vec;
			const Vector& vec2 = stations[neighbor[i][1]].vec;
			double cos1 = Dot(points[i], vec1) * Length(vec2);
			double cos2 = Dot(points[i], vec2) * Length(vec1);
			if (dcmp(cos1 - cos2) < 0)
			{
				neighbor[i][0] = neighbor[i][1];
				neighbor[i][1] = -1;
			}
			else if (dcmp(cos1 - cos2) > 0)
				neighbor[i][1] = -1;
		}
	}

	if (m == 1)
		RunInstance(brute);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("yo.in", "r", stdin);
	freopen("yo.out", "w", stdout);
#endif
	run();
	return 0;
}