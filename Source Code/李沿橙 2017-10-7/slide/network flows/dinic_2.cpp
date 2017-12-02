/* Never say die. */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <string>
#include <map>
#include <set>
#include <bitset>
using namespace std;
int _c = 0;
template <class T> inline void read(T &_a) {
	bool f = 0;
	while (_c < '0' || _c>'9') {if (_c == '-') f = 1; _c=getchar();}
	_a = 0;
	while (_c >= '0' && _c <= '9') {_a = _a * 10 + _c - '0'; _c = getchar();}
	if (f) _a = -_a;
}

#define MAXN 200319
#define MAXM 1000319


struct edge {
	int next, to, f;
} e[(MAXM + MAXN + MAXN) * 2];

int S = 0, T, n;
int head[MAXN], ecnt = 1;

void add(int u, int v) {
	e[++ecnt].to = v; e[ecnt].next = head[u]; e[ecnt].f = 1; head[u] = ecnt;
	e[++ecnt].to = u; e[ecnt].next = head[v]; e[ecnt].f = 0; head[v] = ecnt;
}

int q[MAXN];
int tag[MAXN], cur[MAXN];

bool bfs() {
	memset(tag, 0, sizeof(int) * (2 * n + 2));
	int he = 0, ta = 1; q[he] = S; tag[S] = 1;
	while (he < ta) {
		int x = q[he++];
		for (int now = head[x]; now; now = e[now].next) {
			if (e[now].f && !tag[e[now].to]) {
				tag[e[now].to] = tag[x] + 1;
				q[ta++] = e[now].to;
			}
		}
	}
	return !!tag[T];
}

int dfs(int x) {
	if (x == T) return 1;
	for (int &now = cur[x]; now; now = e[now].next) {
		if (e[now].f && tag[x] < tag[e[now].to]) {
			if (dfs(e[now].to)) {
				e[now].f = 0, e[now^1].f = 1;
				return 1;
			}
		}
	}
	return 0;
}


int main() {
	read(n); T = 2 * n + 1;
	for (int i = 1; i <= n; i++) add(S, i), add(i + n, T);
	for (int i = 1, x, t; i <= n; i++) {
		read(x);
		for (int j = 1; j <= x; j++) read(t), add(i, t + n);
	}
	int ans = 0;
	while (bfs()) {
		for (int i = 2 * n + 2; i--;) cur[i] = head[i]; 
		while (dfs(S)) {
			ans++;	
		}
	}
	printf("%d\n", ans);
	return 0;
}
