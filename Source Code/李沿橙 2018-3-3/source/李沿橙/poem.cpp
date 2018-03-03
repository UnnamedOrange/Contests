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
#include <list>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
typedef long long LL;
typedef unsigned long long ULL;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool minus = false;
	char ch = getchar();
	if (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int maxn = int(3e5) + 5;
const char yes[] = "YES", no[] = "NO";
int n;
int h[maxn];

#define RunInstance(x) delete new x
struct brute1
{
	brute1()
	{
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				for (int k = j + 1; k <= n; k++)
					if (h[i] - h[j] == h[j] - h[k])
					{
						puts(yes);
						return;
					}
		puts(no);
	}
};
struct brute2
{
	inline static void debugPrint(const std::vector<int>& v)
	{
		for (int i = 0; i < v.size(); i++)
		{
			printOut(v[i]);
			putchar(' ');
		}
		putchar('\n');
	}
	brute2()
	{
		std::vector<int> left;
		std::vector<int> right;
		left.reserve(n + 1);
		right.reserve(n + 1);
		for (int i = 2; i <= n; i++)
			right.push_back(h[1] - h[i]);
		std::sort(right.begin(), right.end());
		//debugPrint(right);
		for (int i = 1; i <= n; i++)
		{
			int k = 0;
			for (int j = 0; j < left.size(); j++)
			{
				while (k < right.size() && left[j] > right[k])
					k++;
				if (k == right.size())
					break;
				if (left[j] == right[k])
				{
					puts(yes);
					return;
				}
			}
			if (i != n)
			{
				right.erase(std::lower_bound(right.begin(), right.end(), h[i] - h[i + 1]));
				for (int j = 0; j < right.size(); j++)
					right[j] += h[i + 1] - h[i];

				for (int j = 0; j < left.size(); j++)
					left[j] -= h[i + 1] - h[i];
				left.insert(std::lower_bound(left.begin(), left.end(), h[i] - h[i + 1]), h[i] - h[i + 1]);
				//debugPrint(left);
				//debugPrint(right);
			}
		}
		puts(no);
	}
};
struct cheat
{
	int seq[maxn];
	int left[maxn];
	int right[maxn];

	cheat()
	{
		srand(time(NULL) + clock());
		for (int i = 1; i <= n; i++)
			seq[i] = i;
		srand(clock());
		std::random_shuffle(seq + 1, seq + 1 + n);

		int thresold = std::min(80, n);
		for (int i = 1; i <= thresold; i++)
		{
			int mid = seq[i];
			left[0] = right[0] = 0;
			for (register int j = 1; j < mid; j++)
				left[++left[0]] = h[j] - h[mid];
			for (register int j = mid + 1; j <= n; j++)
				right[++right[0]] = h[mid] - h[j];
			std::sort(left + 1, left + 1 + left[0]);
			std::sort(right + 1, right + 1 + right[0]);

			int k = 1;
			for (int j = 1; j <= left[0]; j++)
			{
				while (k <= right[0] && left[j] > right[k])
					k++;
				if (k > right[0])
					break;
				if (left[j] == right[k])
				{
					puts(yes);
					return;
				}
			}
		}
		puts(no);
	}
};
struct work
{
	class SegTree
	{
		struct Node
		{
			ULL hash;
			ULL revHash;
		};
		Node nodes[maxn * 2];
		static inline int code(int l, int r)
		{
			return (l + r) | (l != r);
		}

		static const ULL p = 131;
		ULL power[maxn];

#define PARAM int l, int r
#define DEF int mid = (l + r) >> 1
#define CNT l, r
#define LC l, mid
#define RC mid + 1, r

		int g_Pos, g_L, g_R, g_Val;
		ULL g_Hash, g_RevHash;

		void update(PARAM)
		{
			DEF;
			Node& t = nodes[code(CNT)];
			Node& lc = nodes[code(LC)];
			Node& rc = nodes[code(RC)];
			t.hash = lc.hash * power[r - mid] + rc.hash;
			t.revHash = rc.revHash * power[mid - l + 1] + lc.revHash;
		}
		void modify_(PARAM)
		{
			Node& t = nodes[code(CNT)];
			if (l == r)
			{
				t.hash = t.revHash = g_Val;
				return;
			}
			DEF;
			if (g_Pos <= mid) modify_(LC);
			if (g_Pos > mid) modify_(RC);
			update(CNT);
		}

		void query_(PARAM)
		{
			Node& t = nodes[code(CNT)];
			if (g_L <= l && r <= g_R)
			{
				g_Hash += t.hash * power[g_R - r];
				g_RevHash += t.revHash * power[l - g_L];
				return;
			}
			DEF;
			if (g_L <= mid) query_(LC);
			if (g_R > mid) query_(RC);
		}

	public:
		SegTree()
		{
			power[0] = 1;
			for (int i = 1; i <= n; i++)
				power[i] = power[i - 1] * p;
		}
		void modify(int pos, int val)
		{
			g_Pos = pos;
			g_Val = val;
			modify_(1, n);
		}
		ULL queryHash(int l, int r)
		{
			g_Hash = 0;
			g_L = l;
			g_R = r;
			query_(1, n);
			return g_Hash;
		}
		ULL queryRevHash(int l, int r)
		{
			g_RevHash = 0;
			g_L = l;
			g_R = r;
			query_(1, n);
			return g_RevHash;
		}
	} st;


	work()
	{
		for (int i = 1; i < n; i++)
		{
			st.modify(h[i], 1);
			int mid = h[i + 1];
			if (mid == 1 || mid == n) continue;
			int range = std::min(mid - 1, n - mid);
			ULL left = st.queryHash(mid - range, mid - 1);
			ULL right = st.queryRevHash(mid + 1, mid + range);
			if (left != right)
			{
				puts(yes);
				return;
			}
		}
		puts(no);
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		h[i] = readIn();

	if (n <= 300)
		RunInstance(brute1);
	else if (n <= 3000)
		RunInstance(brute2);
	else
		RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("poem.in", "r", stdin);
	freopen("poem.out", "w", stdout);
#endif
	run();
	return 0;
}