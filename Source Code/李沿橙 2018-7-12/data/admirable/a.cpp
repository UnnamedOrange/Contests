#include<bits/stdc++.h>

using std :: swap;
using std :: sort;
using std :: unique;
using std :: reverse;
using std :: lower_bound;

#define For(i, _l, _r) for (int i = (_l), i##r = (_r); i <= (i##r); ++i)
#define Lop(i, _l, _r) for (int i = (_l), i##r = (_r); i >= (i##r); --i)
#define Rep(i, _l, _r) for (int i = (_l); i; i = (_r))
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> T max(T x, T y) { return (x > y)? x: y; }
template <typename T> T min(T x, T y) { return (x < y)? x: y; }
template <typename T> bool chkmax(T &x, T y) { return (x >= y)? 0: (x = y, 1); }
template <typename T> bool chkmin(T &x, T y) { return (x <= y)? 0: (x = y, 1); }

template <typename T>
T read(T &in) {
	in = 0; char ch; T f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	while (isdigit(ch)) in = in * 10 + ch - '0', ch = getchar();
	return in *= f;
}

typedef long long LL;
static const int MOD = 1000000009;
static const int MAX1 = 100000 + 11;
static const int MAX2 = 200000 + 11;
static const int MAX_LOG = 18;
static const int SN = 1 << MAX_LOG | 1;
static const double PI = acos(-1);

int add(int x) { return (x >= MOD)? (x - MOD): x; }
int reduce(int x) { return (x < 0)? (x + MOD): x; }
void Add(int &x) { if (x >= MOD) x -= MOD; }
void Reduce(int &x) { if (x < 0) x += MOD; }

struct cpx {
	double r, i;
	cpx(double _r = 0, double _i = 0) { r = _r, i = _i; }
	cpx conj() { return cpx(r, -i); }
};

cpx operator + (const cpx &a, const cpx &b) { return cpx(a.r + b.r, a.i + b.i); }
cpx operator - (const cpx &a, const cpx &b) { return cpx(a.r - b.r, a.i - b.i); }
cpx operator * (const cpx &a, const cpx &b) {
	return cpx(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}

int Ct, Ht[MAX1], Nt[MAX2], to[MAX2];

void ins(int x, int y) {
	Nt[++Ct] = Ht[x], Ht[x] = Ct, to[Ct] = y;
	Nt[++Ct] = Ht[y], Ht[y] = Ct, to[Ct] = x;
}

int N, M, L, R[SN];
cpx PolyA[SN], PolyB[SN], PolyC[SN], PolyD[SN], w[SN];

void FFT(cpx *x) {
	For(i, 0, N - 1) if (i < R[i]) swap(x[i], x[R[i]]);
	for (int i = 1; i < N; i <<= 1)
		for (int j = 0, t = i << 1; j < N; j += t)
			for (int k = 0; k < i; ++k) {
				cpx oA = x[j + k], oB = x[i + j + k] * w[SN / i * k];
				x[j + k] = oA + oB, x[i + j + k] = oA - oB;
			}
}

struct polynomial {
	int *x, n;
	int & operator [] (int n) { return x[n]; }
	const int & operator [] (int n) const { return x[n]; }
	
	polynomial() { x = NULL, n = 0; }
	
	void newlife(int N) {
		n = N, delete[] x, x = new int[N], memset(x, 0, sizeof(int) * N);
	}
	
	void give1(polynomial a) {
		newlife(a.n);
		memcpy(x, a.x, sizeof(int) * n);
	}
	
	void give2(polynomial a) {
		delete[] x, x = a.x, n = a.n;
	}
};

polynomial operator * (polynomial a, polynomial b) {
	polynomial c;
	c.newlife(a.n + b.n - 1);
	
	for (N = 1, L = 0; N < c.n; N <<= 1) ++L;
	For(i, 0, N - 1) R[i] = (R[i >> 1] >> 1) | ((i & 1) << (L - 1));
	
	For(i, 0, a.n - 1) PolyA[i] = cpx(a[i] >> 15, a[i] & 32767);
	For(i, 0, b.n - 1) PolyB[i] = cpx(b[i] >> 15, b[i] & 32767);
	For(i, a.n, N - 1) PolyA[i] = cpx();
	For(i, b.n, N - 1) PolyB[i] = cpx();
	
	FFT(PolyA), FFT(PolyB);
	For(i, 0, N - 1) {
		int j = (N - 1) & (N - i);
		cpx ar = (PolyA[i] + PolyA[j].conj()) * cpx(0.5, 0);
		cpx ai = (PolyA[i] - PolyA[j].conj()) * cpx(0, -0.5);
		cpx br = (PolyB[i] + PolyB[j].conj()) * cpx(0.5, 0);
		cpx bi = (PolyB[i] - PolyB[j].conj()) * cpx(0, -0.5);
		PolyC[i] = ar * br + (ar * bi + ai * br) * cpx(0, 1);
		PolyD[i] = ai * bi;
	}
	FFT(PolyC), FFT(PolyD);
	
	For(i, 0, c.n - 1) {
		int j = (N - 1) & (N - i);
		LL x2 = (LL)(PolyC[j].r / N + 0.5) % MOD << 30;
		LL x1 = (LL)(PolyC[j].i / N + 0.5) % MOD << 15;
		LL x0 = (LL)(PolyD[j].r / N + 0.5);
		
		c[i] = (x2 + x1 + x0) % MOD;
	}
	
	return c;
}

polynomial operator * (polynomial a, int b) {
	polynomial c;
	c.newlife(a.n + 1);
	memcpy(c.x, a.x, sizeof(int) * a.n);
	
	Lop(i, c.n - 1, 1) c[i] = (c[i] + 1ll * b * c[i - 1]) % MOD;
	
	return c;
}

polynomial operator / (polynomial a, int b) {
	polynomial c;
	c.newlife(a.n - 1);
	
	c[0] = a[0];
	For(i, 1, c.n - 1) c[i] = reduce(a[i] - 1ll * c[i - 1] * b % MOD);
	
	return c;
}

int n, k, Ans, sum;
int fa[MAX1], size[MAX1], deg[MAX1];

int fac[MAX1], inv[MAX1];

int S[MAX1], *son[MAX1];

int f[MAX1], *g[MAX1], sf[MAX1], tf[MAX1];

polynomial o[MAX_LOG + 1], P[MAX1], *Q[MAX1], o_o;

void solve(int l, int r, int d = 0) {
	if (l == r) return o[d].newlife(2), o[d][0] = 1, o[d][1] = S[l], void();
	int mid = (l + r) >> 1;
	
	solve(l, mid, d + 1);
	
	o[d].give1(o[d + 1]);
	
	solve(mid + 1, r, d + 1);
	
	o[d].give2(o[d] * o[d + 1]);
}

void DFS(int x) {
	int &len = deg[x];
	
	Rep(i, Ht[x], Nt[i]) if (to[i] != fa[x]) ++len;
	
	son[x] = new int[len];
	
	int ori_len = len;
	
	len = 0;
	
	size[x] = 1;
	Rep(i, Ht[x], Nt[i]) if (to[i] != fa[x]) {
		fa[to[i]] = x, DFS(to[i]), size[x] += size[to[i]];
		son[x][len++] = size[to[i]];
	}
	
	if (!len) return f[x] = 1, void();
	
	memcpy(S, son[x], sizeof(int) * len);
	
	solve(0, len - 1);
	P[x].give1(o[0]);
	
	sort(S, S + len);
	len = unique(S, len + S) - S;
	
	Q[x] = new polynomial[len];
	
	o_o.give2(P[x] * (n - size[x]));
	
	memcpy(son[x], S, sizeof(int) * len);
	For(i, 0, len - 1) Q[x][i].give2(o_o / son[x][i]);
	
	For(i, 0, min(k, ori_len))
		f[x] = (f[x] + 1ll * P[x][i] * fac[k] % MOD * inv[k - i]) % MOD;
	
	g[x] = new int[len]; memset(g[x], 0, sizeof(int) * len);
	For(i, 0, len - 1) For(j, 0, min(k, ori_len))
		g[x][i] = (g[x][i] + 1ll * Q[x][i][j] * fac[k] % MOD * inv[k - j]) % MOD;
}

void DFS1(int x) {
	tf[x] = add(f[x] + tf[fa[x]]);
	Rep(i, Ht[x], Nt[i]) if (to[i] != fa[x]) {
		DFS1(to[i]), Add(sf[x] += sf[to[i]]);
	}
	
	Ans = (Ans + 1ll * f[x] * (sum - sf[x] - tf[x])) % MOD;
	Add(sf[x] += f[x]);
}

void DFS2(int x, int F = 0) {
	Ans = (Ans + 1ll * f[x] * F) % MOD;
	Rep(i, Ht[x], Nt[i]) if (to[i] != fa[x]) {
		DFS2(to[i], add(F + g[x][
		lower_bound(son[x], son[x] + deg[x], size[to[i]]) - son[x]]));
	}
}

int main() {
	
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	
	int SN = ::SN - 1;
	
	For(i, 0, SN - 1) w[i] = cpx(cos(PI / SN * i), sin(PI / SN * i));
	
	read(n), read(k);
	
	For(i, 1, n - 1) {
		int x, y;
		read(x), read(y);
		ins(x, y);
	}
	
	if (k == 1) {
		printf("%lld\n", 1ll * n * (n - 1) / 2 % MOD);
		return 0;
	}
	
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	For(i, 2, max(n, k))
		fac[i] = 1ll * i * fac[i - 1] % MOD,
		inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
	
	For(i, 2, max(n, k)) inv[i] = 1ll * inv[i - 1] * inv[i] % MOD;
	
	DFS(1);
	
	For(i, 1, n) Add(sum += f[i]);
	DFS1(1);
	
	Ans = (Ans + MOD) % MOD * (LL)((MOD + 1) >> 1) % MOD;
	
	DFS2(1);
	
	printf("%d\n", Ans);
	
	return 0;
}
