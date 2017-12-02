#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

const int N = 3e5 + 5;

struct qry {
	int ql, qr, col, fcnt;
	int b1, b2, num; 
	
	bool operator < (const qry &o) const {
		if (b1 == o.b1) {
			if (b2 == o.b2) return fcnt < o.fcnt; 
			else return b2 < o.b2;
		}
		return b1 < o.b1;
	}
} q[N]; 

int qtot, upd[N], ftot; 

int n, m, ks, A[N], ans[N]; 
int l, r, tk[N], hu;

void work() {
	l = 1, r = 0, hu = 0; 
	for (int i = 1; i <= qtot; i ++) {
		int ql = q[i].ql, qr = q[i].qr, qu = q[i].fcnt;
		while (hu < qu) {
			hu ++; 
			if (upd[hu] == r) tk[A[r]] --, tk[A[r + 1]] ++; 
			else if (upd[hu] == l - 1) tk[A[l]] --, tk[A[l - 1]] ++;
			swap(A[upd[hu]], A[upd[hu] + 1]);
		}
		while (hu > qu) { 
			if (upd[hu] == r) tk[A[r]] --, tk[A[r + 1]] ++; 
			else if (upd[hu] == l - 1) tk[A[l]] --, tk[A[l - 1]] ++;
			swap(A[upd[hu]], A[upd[hu] + 1]);
			hu --; 
		}
		while (r < qr) tk[A[++ r]] ++; 
		while (l > ql) tk[A[-- l]] ++; 
		while (r > qr) tk[A[r --]] --;
		while (l < ql) tk[A[l ++]] --;
		
		ans[q[i].num] = tk[q[i].col];
	}
}

int main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);

	scanf("%d%d", &n ,&m);
	ll uu = (ll) n * n; 
	while ((ll) ks * ks * ks < uu) ks ++; 
	for (int i = 1; i <= n; i ++) 
		scanf("%d", A + i);
	for (int i = 1; i <= m; i ++) {
		int type; scanf("%d", &type);
		if (type == 1) {
			int l, r, c; scanf("%d%d%d", &l, &r, &c);
			qtot ++;
			q[qtot].ql = l, q[qtot].qr = r, q[qtot].col = c; 
			q[qtot].fcnt = ftot; 
			q[qtot].b1 = (l / ks) + 1; q[qtot].b2 = (r / ks) + 1;
			q[qtot].num = qtot;
		} else {
			int p; scanf("%d", &p);
			upd[++ ftot] = p; 
		}
	}
	sort(q + 1, q + qtot + 1);
	work();
	for (int i = 1; i <= qtot; i ++)
		printf("%d\n", ans[i]);
	return 0; 
}
