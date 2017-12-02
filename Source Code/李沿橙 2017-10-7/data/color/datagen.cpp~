#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#define rand() ((rand() << 13) ^ (rand() << 16) ^ rand())

LL f[61] = {0, 1};

char a[20];
string in, out;

int aa[300005];

void make(int t) {
	srand(t);
	int n;
	switch (t) {
		case 1 ... 2 : n = 2; break;
		case 3 ... 6 : n = 1000; break;
		case 7 ... 13 : n = 50000; break;
		case 14 ... 20 : n = 300000; break;
	}
	int m1;
	switch (t) {
		case 1 : m1 = 6; break;
		case 2 : m1 = 1000; break;
		default : m1 = n;
	}
	int m2;
	switch (t) {
		case 1 : m2 = 0; break;
		case 3 : m2 = 0; break;
		case 8 : m2 = 0; break;
		case 14 : m2 = 0; break;
		default : m2 = m1;
	}
	int lim;
	switch (t) {
		case 1: lim = 2; break;
		case 2: lim = 1000; break;
		case 4: lim = 10; break;
		case 8: lim = 10; break;
		case 15: lim = 10; break;
		default: lim = n; break;
	}
	int c1 = 0;
	if (t < 3 || t == 10 || t == 17) c1 = 1;
	int c2 = 0;
	if (t < 3 || t == 5 || t == 9 || t == 16) c2 = 1;
	printf("%d %d\n", n, m1 + m2);
	if (t == 1) {
		puts("2 1");
		for (int i = 1; i <= n; i++)
			for (int j = i; j <= n; j++) {
				for (int k = 1; k <= n; k++) {
					printf("1 %d %d %d\n", i, j, k);
				}
			}
	}
	else if (t == 2) {
		puts("123 233");
		while (m1 + m2) {
			if ((rand() & 1) && m1 && m2) {
				int l = rand() % 2 + 1, r = rand() % 2 + 1, c = rand() % 307 + 1;
				if (l > r) swap(l, r);
				printf("1 %d %d %d\n", l, r, c);
				m1--;
			}
			else if (m2) {
				puts("2 1");
				m2--;
			}
			else {
				int l = rand() % 2 + 1, r = rand() % 2 + 1, c = rand() % 307 + 1;
				if (l > r) swap(l, r);
				printf("1 %d %d %d\n", l, r, c);
				m1--;
			}
		}
	}
	else {
		if (c2) for (int i = 1; i <= n ;i++) aa[i] = i;	
		else {
			cerr << lim << endl;
			for (int i = 1; i <= n; i++) aa[i] = i * 5 % (lim) + 1;
		}
		vector < pair<int, int> > bb;
		bb.clear();
		if (c1) for (int i = 1, j; i <= m1; i++) {j = rand() % n + 1; j & 3 ? bb.push_back(make_pair(i % 20 + 1, n - (19 - i % 20))) : bb.push_back(make_pair((j > 20 ? j - 20 : j), (j > 20 ? j : j + 20)));}
		else {
			for (int i = 1; i <= m1 / 2; i++) {
				int x = i % (n / 2) + 1, y = n - rand() % (n - x);
				if (y < n - 16384) y += rand() & 16383;
				if (y < n - 6666) y += rand() % 6666;
				if (x > 2000) x -= rand() % 1000;
				bb.push_back(make_pair(x, y));
			}
			for (int i = 1; i <= m1 / 2; i++) {
				int x = i % (n / 2) + 1;
				bb.push_back(make_pair(x, x + n / 2 - (rand() & 7)));
			}
		}
		random_shuffle(bb.begin(), bb.end());
		random_shuffle(aa + 1, aa + n + 1);
		for (int i = 1; i <= n; i++) {
			printf("%d ", aa[i]);
		}
		puts("");
		while (m1 + m2) {
			if ((rand() & 1) && m1 && m2) {
				m1--;
				printf("1 %d %d %d\n", bb[m1].first, bb[m1].second, rand() & 1 ? (rand() % lim + 1) : (rand() & 1 ? aa[bb[m1].first] : aa[bb[m1].second]));
			}
			else if (m2) {
				if (rand() & 7) printf("2 %d\n", rand() % (n - 1) + 1);
				else printf("2 %d\n", rand() & 1 ? min(n - 1, bb[max(0, m1 - 1)].first) : min(n - 1, bb[max(0, m1 - 1)].second));
				m2--;
			}
			else {
				m1--;
				printf("1 %d %d %d\n", bb[m1].first, bb[m1].second, rand() % lim + 1);
			}
		}
	}
}

int main() {
	for (int i = 1; i <= 20; i++) {
		sprintf(a, "color%d", i);	
		in = a + (string)".in";
		out = a + (string)".out";
		freopen(in.c_str(), "w", stdout);
		make(i);
		fclose(stdout);
		system(("color.exe < " + in + " > " + out).c_str());
	}
	return 0;
}
