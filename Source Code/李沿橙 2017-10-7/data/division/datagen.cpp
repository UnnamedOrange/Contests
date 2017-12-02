#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#define rand() unsigned((rand() << 17) ^ (rand() << 15) ^ rand())

LL f[61] = {0, 1};

char a[20];
string in, out;

int aa[300005];


bool isp(int x) {
	int y = int(sqrt(x) + 0.1);
	return x == y * y;
}

void make(int t) {
	srand(t);
	int n, K;
	switch (t) {
		case 1 : n = 2; break;
		case 2 : n = 4; break;
		case 3 : n = 16; break;
		case 4 : n = 256; break;
		case 5 ... 6 : n = 1024; break;
		case 7 ... 10 : n = 131072; break;
		case 11 : n = 2; break;
		case 12 : n = 4; break;
		case 13 : n = 8; break;
		case 14 : n = 16; break;
		case 15 ... 16 : n = 256; break;
		case 17 ... 18 : n = 1024; break;
		case 19 ... 20 : n = 4096; break;
		case 21 ... 25 : n = 131072; break;
	}
	K = t > 10 ? 2 : 1;
	int lim;
	switch (t) {
		case 7 : lim = 2; break;
		case 17 : lim = 2; break;
		case 19 : lim = 2; break;
		case 21 : lim = 2; break;
		default: lim = 131072; break;
	}
	int c1 = 0;
	if (t == 1 || t == 4 || t == 5 || t == 7 || t == 8 || t == 11 || t == 15 || t == 17) c1 = 1;
	int c2 = 0;
	if (t == 9 || t == 21 || t == 22) c2 = 1;
	printf("%d %d\n", n, K);
	if (t == 1) printf("2 2 ");
	else if (t == 7) {
		for (int i = 1; i <= n / 3; i++) printf("1 ");
		for (int i = n / 3 + 1; i <= n / 2; i++) printf("2 ");
		for (int i = n / 2 + 1; i <= n; i++) printf("1 ");
	}
	else if (t == 11) {
		puts("131072 131072 ");
	}
	else if (t == 12) {
		puts("28928 131072 131072 131072");
	}
	else if (t == 13) {
		puts("2 4 131072 131072 65536 4 2 131072 ");
	}
	else if (t == 14) {
		puts("2 4 4 8 10 2 4 2 6 10 20000 20000 20000 80000 2 80000 ");
	}	
	else if (t == 15) {
		for (int i = 0; i < 64; i++) printf("131072 8 18 2 ");
	}
	else if (t == 17) {
		for (int i = 1; i <= 10; i++) printf("1 ");
		for (int i = 11; i <= n; i++) printf("2 ");
	}
	else if (c2) {
		vector <int> cc; cc.clear();
		for (int i = 1; i <= n; i++) cc.push_back(i);
		random_shuffle(cc.begin(), cc.end());
		for (int i = n; i >= 1; i--) printf("%d ", cc[i - 1]);
	}
	else if (t == 8) {
		int x = (rand() % 350) + 50, xx = x * x, y = rand() % (xx - 1) + 1, z = xx - y;
		while (y == z || y > lim || z > lim) y = rand() % (xx - 1) + 1, z = xx - y;
		vector <int> bb; bb.clear();
		for (int i = 1; i <= 2000; i++) {
			int q = rand() % lim + 1;
			if (isp(q + y) || isp(q + z)) continue;
			bool flag = 1;
			for (vector <int> :: iterator it = bb.begin(); it != bb.end(); it++) {
				if (isp(q + *it)) {flag = 0; break;}
			}
			if (flag) bb.push_back(q);
		}
		printf("%d %d %d ", z, y, y);
		for (int i = 4; i <= n - 1; i++) {
			if (!(rand() % (1 << (22 - (i / 20000)))) && n - 1 - i > 0) {
				swap(y, z);
				printf("%d %d ", y, y);
				i++;
			}
			else {
				printf("%d ", bb[rand() % bb.size()]);
			}
		}
		printf("%d ", z);
	}
	else if (lim == 2) {
		for (int i = 1; i <= n; i++) printf("%d ", rand() % 2 + 1);
	}
	else {
		vector <int> bb; bb.clear();
		for (int i = 1; (i * 2) <= n; i++) {
			int x = (rand() % 370) + 2, xx = x * x, y = rand() % (xx - 1) + 1, z = xx - y;
			while (y > lim || z > lim) y = rand() % (xx - 1) + 1, z = xx - y;
			if (((x & 1) ^ 1) && (rand() & 31) == 31) y = xx / 2, z = y;
			bb.push_back(y), bb.push_back(z);
		}
		for (int i = 1, j; i <= 10; i++) j = rand() % lim + 1, bb.push_back(j), bb.push_back(j);
		random_shuffle(bb.begin(), bb.end());
		if (n < 257) {
			for (int i = 0; i < n / 2; i++) printf("%d %d ", bb[i], lim);
		}
		else if (t == 10) {
			for (int i = 0; i < n / 8; i++) printf("%d ", (rand() % lim) + 1);
			for (int i = 0; i < n / 4; i++) printf("%d ", (((rand() % lim) / 4) * 4) | 1);
			for (int i = 0; i < n / 4; i++) printf("%d ", (rand() % lim) + 1);
			for (int i = 0; i < n / 4; i++) printf("%d ", (((rand() % lim) / 4) * 4) | 1);
			for (int i = 0; i < n / 8; i++) printf("%d ", (rand() % lim) + 1);
			for (int i = 0; i < n / 4; i += 2) {
				if (rand() & (i >> 12)) {
					printf("%d ", rand() & (t | 12) ? bb[i] : lim - (rand() % lim));
					printf("%d ", rand() & (t | 12) ? bb[i] : (rand() % 2 + 1));
				}
				else if (rand() & 31) {
					printf("%d %d ", rand() % lim + 1, rand() % lim + 1);
				}
				else if (!(rand() & 7)) {
					printf("%d %d ", lim - (rand() % min(10, lim)), (rand() % min(lim, 10) + 1));
				}
				else if (i < n - 4) {
					int x = (rand() % 400) + 4, xx = x * x, y = rand() % (xx - 1) + 1, z = xx - y;
					while (y > lim || z > lim) y = rand() % (xx - 1) + 1, z = xx - y;
					if (rand() & 1) y = xx / 2, z = xx / 2; 
					if (rand() & 1) printf("%d %d %d %d ", y, z, z, y);
					else if (rand() & 1) printf("%d %d %d %d ", y, y, z, y);
					else printf("%d %d %d %d ", z, z, z, y);
					i += 2;
				}
				else {
					printf("%d %d ", rand() % lim + 1, rand() % lim + 1);
				}
			}
		}
		else {
			for (int i = 0; i < n / 8; i++) printf("%d ", (rand() % lim) + 1);
			for (int i = 0; i < n / 8; i++) printf("%d ", (((rand() % lim) / 4) * 4) | 1);
			for (int i = 0; i < n / 4; i++) printf("%d ", (rand() % lim) + 1);
			for (int i = 0; i < n / 2; i += 2) {
				if (rand() & (i >> 12)) {
					printf("%d ", rand() & (t | 12) ? bb[i] : lim - (rand() % lim));
					printf("%d ", rand() & (t | 12) ? bb[i] : (rand() % 2 + 1));
				}
				else if (rand() & 31) {
					printf("%d %d ", rand() % lim + 1, rand() % lim + 1);
				}
				else if (!(rand() & 7)) {
					printf("%d %d ", lim - (rand() % min(10, lim)), (rand() % min(lim, 10) + 1));
				}
				else if (i < n - 4) {
					int x = (rand() % 400) + 4, xx = x * x, y = rand() % (xx - 1) + 1, z = xx - y;
					while (y > lim || z > lim) y = rand() % (xx - 1) + 1, z = xx - y;
					if (rand() & 1) y = xx / 2, z = xx / 2; 
					if (rand() & 1) printf("%d %d %d %d ", y, z, z, y);
					else if (rand() & 1) printf("%d %d %d %d ", y, y, z, y);
					else printf("%d %d %d %d ", z, z, z, y);
					i += 2;
				}
				else {
					printf("%d %d ", rand() % lim + 1, rand() % lim + 1);
				}
			}
		}
	}
	puts("");
}

int main() {
	for (int i = 1; i <= 25; i++) {
		sprintf(a, "division%d", i);	
		in = a + (string)".in";
		out = a + (string)".out";
		freopen(in.c_str(), "w", stdout);
		make(i);
		fclose(stdout);
		//cerr << ("division.exe < " + in + " > " + out) << endl;
		system(("division.exe < " + in + " > " + out).c_str());
	//	system(("fc " + out +  " " + (string)a + ".out").c_str());
	}
	return 0;
}
