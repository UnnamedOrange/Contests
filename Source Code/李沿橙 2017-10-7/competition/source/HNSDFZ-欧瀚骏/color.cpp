#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 300000
#define MAX 20000000
using namespace std;
typedef long long LL;
int root[N + 5], son[MAX + 5][2], s[MAX + 5], a[N + 5], cnt = 0, n, m;
int newnode(int rt) {
	int p = ++cnt;
	memcpy(son[p], son[rt], sizeof(son[p]));
	s[p] = s[rt];
	return p;
}
int add(int x, int rt) {
	int l = 0, r = N, p = newnode(rt), tmp = p;
	while (l < r) {
		int mid = l + r >> 1;
		if (x <= mid) son[p][0] = newnode(son[rt][0]), p = son[p][0], rt = son[rt][0], r = mid;
					else son[p][1] = newnode(son[rt][1]), p = son[p][1], rt = son[rt][1], l = mid + 1;
	}
	s[p] = s[rt] + 1;
//	printf("p = %d rt = %d %d %d\n", p, rt, s[p], s[rt]);
	return tmp;
}
void insert(int p, int x, int c) {
	int l = 0, r = N;
//	printf("insert %d %d %d\n", p, x, c);
	while (l < r) {
		int mid = l + r >> 1;
		if (x <= mid) son[p][0] = newnode(son[p][0]), p = son[p][0], r = mid; 
					else son[p][1] = newnode(son[p][1]), p = son[p][1], l = mid + 1;
	}
	s[p] += c;
//	printf("p = %d c = %d\n", p, c);
}
int query(int ll, int rr, int x) {
	ll = root[ll - 1], rr = root[rr];
	int l = 0, r = N; 
	while (l < r) {
		int mid = l + r >> 1;
		if (x <= mid) ll = son[ll][0], rr = son[rr][0], r = mid;
					else ll = son[ll][1], rr = son[rr][1], l = mid + 1;
	}
//	printf("ll = %d rr = %d\n", ll, rr);
	return s[rr] - s[ll];
}
int main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) { scanf("%d", a + i); root[i] = add(a[i], root[i - 1]); }
	while (m--) {
		int op, l, r, x;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d%d", &l, &r, &x);
			printf("%d\n", query(l, r, x));
		}
		if (op == 2) {
			scanf("%d", &x);
			insert(root[x], a[x + 1], 1);
			insert(root[x], a[x], -1);
			swap(a[x], a[x + 1]);
		}
	}
	return 0;
}
