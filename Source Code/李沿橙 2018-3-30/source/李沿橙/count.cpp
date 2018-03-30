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
typedef long long INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		a = a * 10 - (ch - '0');
		ch = getchar();
	}
	if (positive) a = -a;
	return a;
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

const double PI = std::acos(-1);
const int maxn = 1005;
int n, m;

#define DefinePoint(name)\
struct name\
{\
	double x, y;\
	name() {}\
	name(const double& x, const double& y) : x(x), y(y) {}\
}
DefinePoint(Point);
DefinePoint(Vector);
int dcmp(const double& x)
{
	const double EPS = 1e-6;
	if (std::abs(x) < EPS) return 0;
	return x < 0 ? -1 : 1;
}
bool operator==(const Point& a, const Point& b)
{
	return !dcmp(a.x - b.x) && !dcmp(a.y - b.y);
}
Vector operator-(const Point& a, const Point& b)
{
	return Vector(b.x - a.x, b.y - a.y);
}
struct Segment
{
	Point a, b;
	Segment() {}
	Segment(const Point& a, const Point& b) : a(a), b(b) {}
	operator Vector() const { return a - b; }
};
double Dot(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y;
}
double Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}
double Length(const Vector& a)
{
	return std::sqrt(Dot(a, a));
}
bool OnSegment(const Point& p, const Segment& seg)
{
	return dcmp(Cross(seg.a - p, seg)) == 0 && dcmp(Dot(p - seg.a, p - seg.b)) <= 0;
}
bool IsSegmentsIntersected(const Segment& a, const Segment& b)
{
	if (dcmp(Cross(a.a - a.b, a.a - b.a)) * dcmp(Cross(a.a - a.b, a.a - b.b)) >= 0) return false;
	if (dcmp(Cross(b.a - b.b, b.a - a.a)) * dcmp(Cross(b.a - b.b, b.a - a.b)) >= 0) return false;
	return true;
}

#define RunInstance(x) delete new x
struct brute
{
#define fo(name, to) for(int name = 1; name <= to; name++)
	brute()
	{
		LL ans = 0;
		fo(x1, n)
			fo(y1, m)
			fo(x2, n)
			fo(y2, m)
			if (!(x1 == x2 && y1 == y2))
				fo(x3, n)
				fo(y3, m)
				if (!(x1 == x3 && y1 == y3) && !(x2 == x3 && y2 == y3))
					fo(x4, n)
					fo(y4, m)
					if (!(x1 == x4 && y1 == y4) && !(x2 == x4 && y2 == y4) && !(x3 == x4 && y3 == y4))
					{
						Point p1(x1, y1);
						Point p2(x2, y2);
						Point p3(x3, y3);
						Point p4(x4, y4);
						if (!dcmp(Cross(p1 - p2, p2 - p3))) break;
						if (!dcmp(Cross(p2 - p3, p3 - p4))) continue;
						if (!dcmp(Cross(p3 - p4, p4 - p1))) continue;
						if (!dcmp(Cross(p4 - p1, p1 - p2))) continue;
						if (IsSegmentsIntersected(Segment(p1, p2), Segment(p3, p4))) continue;
						if (IsSegmentsIntersected(Segment(p2, p3), Segment(p1, p4))) continue;
						ans++;
					}
		printOut(ans / 8);
	}
};

struct calc
{
	LL on[20][20];
	LL in[20][20];
	LL out[20][20];
	LL at[20][20];
	calc() : on(), in(), out(), at()
	{
		fo(x1, n)
			fo(y1, m)
			fo(x2, n)
			fo(y2, m)
			if (!(x1 == x2 && y1 == y2))
				fo(x3, n)
				fo(y3, m)
				if (!(x1 == x3 && y1 == y3) && !(x2 == x3 && y2 == y3))
				{
					Point p1(x1, y1);
					Point p2(x2, y2);
					Point p3(x3, y3);
					if (!dcmp(Cross(p1 - p2, p2 - p3))) continue;
					fo(x4, n)
						fo(y4, m)
					{
						Point p4(x4, y4);
						if (p1 == p4 || p2 == p4 || p3 == p4)
						{
							at[x4][y4]++;
							continue;
						}
						if (OnSegment(p4, Segment(p1, p2)) || OnSegment(p4, Segment(p2, p3)) || OnSegment(p4, Segment(p3, p1)))
						{
							on[x4][y4]++;
							continue;
						}
						Vector v1 = p4 - p1;
						Vector v2 = p4 - p2;
						Vector v3 = p4 - p3;

						double a1 = std::acos(Dot(v1, v2) / Length(v1) / Length(v2)) * dcmp(Cross(v1, v2));
						double a2 = std::acos(Dot(v2, v3) / Length(v2) / Length(v3)) * dcmp(Cross(v2, v3));
						double a3 = std::acos(Dot(v3, v1) / Length(v3) / Length(v1)) * dcmp(Cross(v3, v1));
						if (dcmp(a1 + a2 + a3))
							in[x4][y4]++;
						else
							out[x4][y4]++;
					}
				}
		puts("at:");
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				printf("%lld ", at[i][j] /= 6);
			puts("");
		}
		puts("on:");
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				printf("%lld ", on[i][j] /= 6);
			puts("");
		}
		puts("in:");
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				printf("%lld ", in[i][j] /= 6);
			puts("");
		}
		puts("out:");
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				printf("%lld ", out[i][j] /= 6);
			puts("");
		}
		LL IN = 0;
		LL OUT = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				IN += in[i][j];
				OUT += out[i][j];
			}
		}
		printOut(OUT / 4);
	}
};

void run()
{
	n = readIn() + 1;
	m = readIn() + 1;
	RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("count.in", "r", stdin);
	freopen("count.out", "w", stdout);
#endif
	run();
	return 0;
}