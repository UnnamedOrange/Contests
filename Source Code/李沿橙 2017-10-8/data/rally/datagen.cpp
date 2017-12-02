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
	srand(t + 1123);
	int n, m, K;
	switch (t) {
		case 1 : n = 2; break;
		case 2 ... 3 : n = 4; break;
		case 4 ... 7 : n = 16; break;
		case 9 ... 11 : n = 80; break;
		default : n = 400;
	}
	switch (t) {
		case 2 : m = 2; break;
		case 4 : m = 2; break;
		case 8 : m = 2; break;
		case 12 : m = 2; break;
		default : m = n;
	}
	switch (t) {
		case 5 : K = 2; break;
		case 9 : K = 2; break;
		case 13 ... 14 : K = 2; break;
		case 17 ... 18 : K = 400; break;
		default : K = 1000000;
	}
	if (K > 2) K = int((LL)K * (800000 + (rand() % 200001)) / 1000000);
	if (t == 6 || t == 10 || t == 14 || t == 15 || t == 16) {
		if (K % 2) K++;
		int p = rand() % K + 1;
		for (int c = 0; c < 1000000 && ((LL)p * n < K || K % p != 0); c++) p = rand() % K + 1;
		if (K % p != 0) p = K / 2;
		if (n == m) m -= rand() & 3, n -= rand() & 3;
		printf("%d %d %d\n", n, m, K);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				printf("%d ", p);
			}
			printf("\n");
		}
	}
	else {
		if (n <= 16 && m <= 16) {
			printf("%d %d %d\n", n, m, K);
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (rand() & 1) printf("%d ", rand() % K + 1);
					else printf("%d ", K);
				}
			}
		}
		else if (n < 300 || m < 300) {
			if (n == m && n > 4) m -= rand() & 3, n -= rand() & 3;
			printf("%d %d %d\n", n, m, K);
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (rand() & 15) printf("%d ", rand() % K + 1);
					else printf("%d ", K);
				}
			}
		}
		else {
			if (K & 1) K++;
			if (n == m && n > 4) m -= rand() & 3, n -= rand() & 3;
			printf("%d %d %d\n", n, m, K);
			for (int i = 1; i <= n; i++) 
				for (int j = 1; j <= m; j++) {
					if (i > 30 && i < 360 && j > 20 && j < 318) printf("%d ", K);  
					else if (rand() & 31) printf("%d ", K);
					else if (rand() & 3) printf("%d ", K / 2);
					else printf("%d ", rand() % K + 1);
				}
		}
	}
}

int main() {
	for (int i = 1; i <= 20; i++) {
		sprintf(a, "rally%d", i);	
		in = a + (string)".in";
		out = a + (string)".out";
		freopen(in.c_str(), "w", stdout);
		make(i);
		fclose(stdout);
		//cerr << ("rally.exe < " + in + " > " + out) << endl;
		system(("rally.exe < " + in + " > " + out).c_str());
	//	system(("fc " + out +  " " + (string)a + ".out").c_str());
	}
	return 0;
}
