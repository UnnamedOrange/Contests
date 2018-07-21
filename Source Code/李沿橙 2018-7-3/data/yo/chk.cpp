#include "testlib.h"

#define pb push_back
#define fi first
#define se second

using namespace std;

typedef double ld;
typedef pair <ld, int> pi;

const int N = 200005;
const ld PI = acos(-1), eps = 1e-7;

int n, m, cnt[N], nr_a[N], nr_b[N];
vector <pi> a, b;
ld go (ld u, ld v) { return v + eps > u ? v - u : v - u + 2 * PI; }
bool vis[N];

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	int your_ans = ouf.readInt(), std_ans = ans.readInt();
	if (your_ans < std_ans) quitf(_wa, "your answer is smaller than std");
	int i, j, k, x, y;
	n = inf.readInt(), m = inf.readInt();
	for (i = 0; i < n; i ++) x = inf.readInt(), y = inf.readInt(), a.pb(pi(atan2(y, x), i));
	for (i = 0; i < m; i ++) x = inf.readInt(), y = inf.readInt(), cnt[i] = inf.readInt(), b.pb(pi(atan2(y, x), i));
	memset (nr_a, -1, sizeof(nr_a)), memset (nr_b, -1, sizeof(nr_b));
	if (m == 1) {
		for (i = 0; i < n; i ++) nr_a[i] = 0;
	} else {
		sort (a.begin(), a.end()), sort (b.begin(), b.end());
		for (i = j = 0; i < n; i ++) {
			while (fabs(go(b[j].fi, a[i].fi) + go(a[i].fi, b[(j + 1) % m].fi) - go(b[j].fi, b[(j + 1) % m].fi)) > eps)
				j = (j + 1) % m;
			k = (j + 1) % m;
			if (fabs(go(b[j].fi, a[i].fi) - go(a[i].fi, b[k].fi)) < eps) {
				nr_a[a[i].se] = b[j].se;
				nr_b[a[i].se] = b[k].se;
			} else if (go(b[j].fi, a[i].fi) < go(a[i].fi, b[k].fi)) {
				nr_a[a[i].se] = b[j].se;
			} else {
				nr_a[a[i].se] = b[k].se;
			}
		}
	}
	for (i = 0; i < your_ans; i ++) {
		x = ouf.readInt(), y = ouf.readInt();
		if (vis[x]) quitf(_wa, "illegal choice 1");
		vis[x] = true;
		if (nr_a[x] != y && nr_b[x] != y) quitf(_wa, "illegal choice 2");
		if (--cnt[y] < 0) quitf(_wa, "illegal choice 3");
	}
	if (your_ans > std_ans) quitf(_ok, "std error");
	else quitf(_ok, "ok");
}
