#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#define rand() unsigned((rand() << 17) ^ (rand() << 15) ^ rand())

LL f[61] = {0, 1};

char a[20];
string in, out;


void make(int t) {
	srand(t + 1123);
	int n, m, K, lim;
	switch (t) {
		case 1 : n = 2; break;
		case 2 ... 3 : n = 4; break;
		case 4 ... 6 : n = 16; break;
		case 7 ... 14 : n = 200; break;
		case 15 ... 25 : n = 40000; break;
	}
	switch (t) {
		case 1 : m = 2; break;
		case 2 : m = 1; break;
		case 4 : m = 1; break;
		case 7 ... 8: m = 1; break;
		case 9 ... 11 : m = 4; break;
		case 15 ... 17: m = 1; break;
		case 18 ... 20: m = 4; break;
		default : m = min(n, 64);
	}
	switch (t) {
		case 7 : lim = 2; break;
		case 9 ... 11 : lim = 4; break;
		case 15 : lim = 2; break;
		case 18 ... 20 : lim = 4; break;
		default : lim = n;
	}
	K = t == 1 ? 1 : (t < 4 ? 4 : 8);
	if (t == 1) {
		printf("2 2 2\n1 2 \n1 2 \n");
	}
	else if (t == 2) {
		printf("4 2 1\n1 4 \n2 \n");
	}
	else if (t == 3) {
		printf("4 3 2\n1 3 4 \n2 3 \n");
	}
	else if (t == 13) {
		printf("200 6 64\n");
		printf("2 3 5 6 8 9 \n");
		for (int i = 0; i < 64; i++) printf("%d ", i + 4);
		puts("");
	}
	else if (t == 16) {
		printf("40000 8 1\n");
		printf("200 201 202 203 300 301 302 303 \n");
		puts("100 ");
	}
	else if (t == 22) {
		printf("40000 7 64\n");
		printf("200 201 202 300 301 302 303 \n");
		for (int i = 0; i < 64; i++) printf("%d ", i + 99);
		puts("");
	}
	else if (m == 4) {
		printf("%d %d %d\n", n, K, n < 20 ? 3 : 2);
		vector <int> b; b.clear();
		while (b.size() != K) {
			for (int i = 0; i < K; i++) b.push_back(rand() % n + 1);
			sort(b.begin(), b.end());
			if (unique(b.begin(), b.end()) != b.end()) b.clear();
		}
		for (int i = 0; i < K; i++) printf("%d ", b[i]);
		if (n < 20) printf("\n1 2 3 \n");
		else printf("\n2 3 \n");
	}
	else if (m == 1) {
		int p = 6;
		if (lim == 2) p = 2;
		K = p;
		while (K * 2 <= 8) K *= 2;
		printf("%d %d %d\n", n, K, 1);
		vector <int> b; b.clear();
		while (b.size() != K) {
			for (int i = 0; i < K; i++) b.push_back(rand() % n + 1);
			sort(b.begin(), b.end());
			if (unique(b.begin(), b.end()) != b.end()) b.clear();
		}
		for (int i = 0; i < K; i++) printf("%d ", b[i]);
		printf("\n%d \n", 2);
	}
	else {
		if (n == 16) {
			printf("16 8 8\n");
			vector <int> b; b.clear();
			while (b.size() != K) {
				for (int i = 0; i < K; i++) b.push_back(rand() % n + 1);
				sort(b.begin(), b.end());
				if (unique(b.begin(), b.end()) != b.end()) b.clear();
			}
			for (int i = 0; i < K; i++) printf("%d ", b[i]);
			printf("\n2 3 4 5 7 8 9 11 \n");
		}
		else {
			printf("%d %d %d\n", n, K, m);
			vector <int> b; b.clear();
			while (b.size() != K) {
				for (int i = 0; i < K; i++) b.push_back(rand() % n + 1);
				sort(b.begin(), b.end());
				if (unique(b.begin(), b.end()) != b.end()) b.clear();
			}
			for (int i = 0; i < K; i++) printf("%d ", b[i]);
			puts("");
			int last = 2;
			for (int i = 0; i < m; i++) printf("%d ", last), last += rand() % (n < 1000 ? 3 : 100) + 1;
		}
	}
}

int main() {
	for (int i = 1; i <= 25; i++) {
		sprintf(a, "starlit%d", i);	
		in = a + (string)".in";
		out = a + (string)".out";
		freopen(in.c_str(), "w", stdout);
		make(i);
		fclose(stdout);
		//cerr << ("starlit.exe < " + in + " > " + out) << endl;
		system(("starlit.exe < " + in + " > " + out).c_str());
	//	system(("fc " + out +  " " + (string)a + ".out").c_str());
	}
	return 0;
}
