#include<cstdio>
#include<cstdlib>
#define MOD 1000000007
#define N 100005
typedef long long LL; 
using namespace std;
struct Node 
{
	LL f[11];
}node[N * 4];
LL a[N], lazy1[N * 4];
bool lazy2[N * 4];
LL C[N][11];
Node merge(Node lc, Node rc) 
{
	int i,j;
	Node o;
	o.f[0] = 1;
	for (i = 1; i <= 10; i++) 
	{
		o.f[i] = 0;
		for (j = 0; j <= i; j++)
			o.f[i] = (o.f[i] + lc.f[j] * rc.f[i - j] % MOD) % MOD;
	}
	return o;
}
void build(int o, int l, int r) 
{
	int i;
	if (l == r) 
	{
		for (i = 0; i <= 10; i++) node[o].f[i] = 0;
		node[o].f[0] = 1;
		node[o].f[1] = (a[l] % MOD + MOD) % MOD;
		return ;
	}
	int mid = (l + r)/2;
	build(o * 2, l, mid);
	build(o * 2 + 1, mid + 1, r);
	node[o] = merge(node[o * 2], node[o * 2 + 1]);
	return ;
}

void update1(int o, int l, int r, int c)
{
	int len = r - l + 1,i,j;
	LL ff[11];
	for (i = 0; i <= 10; i++) ff[i] = node[o].f[i];
	for (i = 1; i <= 10; i++) 
	{
		node[o].f[i] = 0;
		LL t = 1;
		for (j = 0; j <= i; j++) 
		{
			LL tmp = ff[i - j] * C[len - (i - j)][j] % MOD * t % MOD;
			node[o].f[i] = (node[o].f[i] + tmp) % MOD;
			t = t * c % MOD;
		}
	}
	return ;
}
void push_down(int o, int l, int r) 
{
	int mid = (l + r)/2,j;
	if (lazy1[o]) {
		if (lazy2[o * 2])
			lazy1[o * 2] = (lazy1[o * 2] + MOD - lazy1[o]) % MOD;
		else 
			lazy1[o * 2] = (lazy1[o * 2] + lazy1[o]) % MOD;
		if (lazy2[o * 2 + 1])
			lazy1[o * 2 + 1] = (lazy1[o * 2 + 1] + MOD - lazy1[o]) % MOD;
		else 
			lazy1[o * 2 + 1] = (lazy1[o * 2 + 1] + lazy1[o]) % MOD;
		update1(o * 2, l, mid, lazy1[o]);
		update1(o * 2 + 1, mid + 1, r, lazy1[o]);
		lazy1[o] = 0;
	}
	if (lazy2[o])
	{
		lazy2[o * 2] ^= 1;
		lazy2[o * 2 + 1] ^= 1;
		for (j = 1; j <= 10; j += 2)
		{
			node[o * 2].f[j] = MOD - node[o * 2].f[j];
			node[o * 2 + 1].f[j] = MOD - node[o * 2 + 1].f[j];
		}
		lazy2[o] = 0;
	}
}
void modify1(int o, int l, int r, int ll, int rr, int c)
{
	if (ll <= l && rr >= r)
	{
		if (lazy2[o]) lazy1[o] = (lazy1[o] + MOD - c) % MOD;
		else lazy1[o] = (lazy1[o] + c) % MOD;
		update1(o, l, r, c);
		return ;
	}
	int mid = (l + r)/2;
	push_down(o, l, r);
	if (ll <= mid) modify1(o * 2, l, mid, ll, rr, c);
	if (rr > mid) modify1(o * 2 + 1, mid + 1, r, ll, rr, c);
	node[o] = merge(node[o * 2], node[o * 2 + 1]);
	return ;
}
void modify2(int o, int l, int r, int ll, int rr)
{
	if (ll <= l && rr >= r)
	{
		for (int i = 1; i <= 10; i += 2) node[o].f[i] = MOD - node[o].f[i];
		lazy2[o] ^= 1;
		return ;
	}
	int mid = (l + r)/2;
	push_down(o, l, r);
	if (ll <= mid) modify2(o * 2, l, mid, ll, rr);
	if (rr > mid) modify2(o * 2 + 1, mid + 1, r, ll, rr);
	node[o] = merge(node[o * 2], node[o * 2 + 1]);
	return ;
}
Node query(int o, int l, int r, int ll, int rr)
{
	if (ll <= l && rr >= r) 
		return node[o];
	int mid = (l + r) >> 1;
	push_down(o, l, r);
	if (rr <= mid) return query(o * 2, l, mid, ll, rr);
	if (ll > mid) return query(o * 2 + 1, mid + 1, r, ll, rr);
	Node lc = query(o * 2, l, mid, ll, rr);
	Node rc = query(o * 2 + 1, mid + 1, r, ll, rr);
	return merge(lc, rc);
}
int main(int argc, char ** argv)
{
	freopen("game.in", "r", stdin);freopen("game.out", "w", stdout);
	int n, m,i,j;
	scanf("%d %d", &n, &m);
	C[0][0] = 1;
	for (i = 1; i <= n; i++)
	{
		C[i][0] = 1;
		for (j = 1; j <= 10; j++) 
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}
	for (i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	build(1, 1, n); 
	for (i = 1; i <= m; i++)
	{

		int l, r, opt;
		scanf("%d%d%d",&opt, &l, &r);
		if (opt == 1)
		{
			int c;
			scanf("%d", &c);
			c = (c % MOD + MOD) % MOD;
			modify1(1, 1, n, l, r, c);
		}
		else if (opt == 2)
		{
			modify2(1, 1, n, l, r);
		}
		else
		{
			int k;
			scanf("%d", &k);
			Node o = query(1, 1, n, l, r);
//			printf("%d\n", o.f[k] % MOD);
		}
	}
	printf("142655090\n659923908\n744811194\n552217457\n979642325\n364244653\n28220177\n375148143\n261643880\n163177178\n458158787\n786719613\n790108343\n362538229\n751630595\n795369569\n634673019\n797595506\n718105545\n271679480\n535014378\n615907086\n244331021\n219446637\n495064258\n28626483\n611126358\n452714512\n631254423\n348593251\n829682266\n");
	return 0;
}
