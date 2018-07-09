#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set> 
#include <algorithm>

#define iter(i, n) for (int i = 1; i <= n; ++i)
#define iter0(i, n) for (int i = 0; i < n; ++i)
#define iter_r(i, n) for (int i = n; i >= 1; --i)

int n, m, type;

int main() {
	FILE *fin = fopen("tree10.in", "r");
	FILE *fout = fopen("tree10.out", "r");
	FILE *fenc = fopen("tree10.in.enc", "w");
	
	fscanf(fin, "%d%d%d", &n, &m, &type);
	fprintf(fenc, "%d %d 1\n", n, m);
	iter(i, n - 1) {
		int x, y, z;
		fscanf(fin, "%d %d %d\n", &x, &y, &z);
		fprintf(fenc, "%d %d %d\n", x, y, z);
	}
	long long lst = 0;
	iter(i, m) {
		char op[20]; int a, b, c;
		fscanf(fin, "%s", op);
		if (op[0] == 'm') {
			fscanf(fin, "%d%d", &a, &b);
			a ^= lst, b ^= lst;
			fprintf(fenc, "%s %d %d\n", op, a, b);
		} else {
			fscanf(fin, "%d%d%d", &a, &b, &c);
			a ^= lst, b ^= lst, c ^= lst;
			fprintf(fenc, "%s %d %d %d\n", op, a, b, c);
		}
		fscanf(fout, "%lld", &lst); lst %= n;
	}
	return 0;
}
