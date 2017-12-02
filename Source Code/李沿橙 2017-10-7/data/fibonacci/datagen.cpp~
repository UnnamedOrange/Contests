#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL f[61] = {0, 1};

char a[20];
string in, out;



void make(int t) {
	int m = t;
	if (t < 5) m += 10;
	else if (t < 8) m += 1000;
	else m += 300000;
	printf("%d\n", m);
	puts("2 3\n3 3");
	m -= 2;
	LL lim;
	switch (t) {
		case 1 ... 2 : lim = 15; break;
		case 3 ... 4 : lim = 1000; break;
		case 5 ... 7 : lim = 1000000; break;
		case 8 ... 10 : lim = 1000000000000ll; break;
	}
	cerr << t << " " << lim << endl;
	if (t == 1) {
		for (int i = 1; i <= 3; i++) {
			for (int j = 1; j <= 3; j++) {
				printf("%d %d\n", i, j);	
			}
		}
	}
	else if (t == 3 || t == 5 || t == 8) {
		int p = 1;
		for (p = 1; f[p] <= lim; p++); p--;
		for (int i = 1; i <= m; i++) {
			printf("%lld %lld\n", f[rand() % p + 1], f[rand() % p + 1]);
		}
	}
	else if (t == 6 || t == 9) {
		for (int i = 1; i <= m; i++) {
			lim--;
			LL x = ((LL)rand() << 16) ^ ((LL) rand() << 30) ^ rand();
			x %= lim; x++;
			printf("%lld %lld\n", x, x + (rand() & 1));
		}
	}
	else {
		for (int i = 1; i <= m; i++) {
			LL x = ((LL)rand() << 16) ^ ((LL) rand() << 30) ^ rand();
			x %= lim; x++;
			LL y = ((LL)rand() << 16) ^ ((LL) rand() << 30) ^ rand();
			y %= lim; y++;
			printf("%lld %lld\n", x, y);
		}
	}
}

int main() {
	for (int i = 2; i <= 60; i++) f[i] = f[i - 1] + f[i - 2];
	for (int i = 1; i <= 10; i++) {
		sprintf(a, "fibonacci%d", i);	
		in = a + (string)".in";
		out = a + (string)".out";
		freopen(in.c_str(), "w", stdout);
		make(i);
		fclose(stdout);
		system(("fibonacci.exe < " + in + " > " + out).c_str());
	}
	return 0;
}
