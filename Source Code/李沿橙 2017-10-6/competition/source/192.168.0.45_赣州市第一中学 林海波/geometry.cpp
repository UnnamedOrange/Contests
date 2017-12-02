#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 100010;
const double eps = 1e-10;

using namespace std;

struct Point
{
	int x;
	int y;
	Point(int xi = 0, int yi = 0) : x(xi), y(yi) {}
	void get_point_x() { scanf("%d", &x); }
	void get_point_y() { scanf("%d", &y); }
	void get_point() { scanf("%d%d", &x, &y); }
	inline Point operator-(Point p)
	{ return Point(x - p.x, y - p.y); }
};

typedef Point Vector;

int n, m;
Point points_x[maxn];
Point points_y[maxn];
Point point_q;

inline double cross(Vector v1, Vector v2);

inline bool has_point(int i);

int main()
{
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		points_x[i].get_point_x();
	for (int i = 1; i <= n; i++)
		points_y[i].get_point_y();
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		point_q.get_point();
		int l = 0;
		int r = n;
		while (l < r)
		{
			int mid = (l + r + 1) / 2;
			if (has_point(mid))
				l = mid;
			else
				r = mid - 1;
		}
		printf("%d\n", l);
	}
	return 0;
}

inline double cross(Vector v1, Vector v2)
{
	return double(v1.x) * v2.y - double(v1.y) * v2.x;
}

inline bool has_point(int i)
{
	if (i == 0)
		return false;
	Vector & v1 = point_q;
	Vector v2 = points_x[i] - points_y[i];
	Vector & w = points_y[i];
	double t = cross(w, v2) / cross(v1, v2);
	if (eps <= (t - 0) && (t - 1) <= eps)
		return true;
	else
		return false;
}

