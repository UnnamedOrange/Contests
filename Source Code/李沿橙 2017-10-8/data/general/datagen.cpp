#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#define rand() unsigned((rand() << 17) ^ (rand() << 15) ^ rand())


char a[20];
string in, out;

int f[123123];


vector <pair <int, int> > e;

void make(int t) {
	srand(t + 21123);
	int n, m, K;
	switch (t) {
		case 2 ... 3 : n = 16; break;
		case 4 ... 5 : n = 100; break;
		case 10 ... 11 : n = 16; break;
		case 12 ... 13 : n = 10; break;
		case 16 : n = 16; break;
		case 17 ... 18 : n = 17; break; 
		default : n = 100000;
	}
	switch (t) {
		case 1 : K = 0; break;
		case 2 ... 9 : K = 1; break;
		case 10 ... 15 : K = 2; break;
		case 16 ... 18 : K = 3; break;
		default : K = 20;
	}
	int tt;
	switch (t) {
		case 5 : tt = 1; break;
		case 6 ... 7 : tt = 2; break;
		case 14 : tt = 1; break;
		case 19 : tt = 1; break;
		default : tt = 0;
	}
	if (n > 10000 && K > 10) K = 4;
	printf("%d %d %d\n", n, K, tt);
	for (int i = 1; i <= n; i++) f[i] = i;
	random_shuffle(f + 1, f + n + 1);
	e.clear();
	if (tt == 1) {
		for (int i = 2; i <= 7; i++) e.push_back(make_pair(i - 1, i));
		e.push_back(make_pair(4, 8));
		for (int i = 9; i <= n; i++) e.push_back(make_pair(rand() % 8 + 1, i));
	}
	else if (tt == 2) {
		for (int i = 1; i <= n; i++) if (f[i] == 1) {swap(f[i], f[1]); break;}
		if (t & 1) {
			e.push_back(make_pair(1, 2)); e.push_back(make_pair(2, 3)); e.push_back(make_pair(2, 4));
			for (int i = 5; i <= n; i++) e.push_back(make_pair(1, i));
		}
		else {
			e.push_back(make_pair(1, 2)); e.push_back(make_pair(1, 3));
			for (int i = 4; i <= n; i++) e.push_back(make_pair(3, i));
		}
	}
	else {
		if (n < 20) {
			for (int i = 2; i <= n; i++) e.push_back(make_pair(rand() % (i - 1) + 1, i));
		}
		else {
			for (int i = 2; i <= n / 4; i++) e.push_back(make_pair(i - 1, i));
			for (int i = n / 4 + 1; i <= n; i++) e.push_back(make_pair(rand() % (i - 1) + 1, i));
		}
	}
	random_shuffle(e.begin(), e.end());
	for (int i = 0; i < n - 1; i++) 
		if (rand() & 1) printf("%d %d\n", f[e[i].first], f[e[i].second]);
		else printf("%d %d\n", f[e[i].second], f[e[i].first]);
}

int main() {
	for (int i = 1; i <= 20; i++) {
		sprintf(a, "general%d", i);	
		in = a + (string)".in";
		out = a + (string)".out";
		freopen(in.c_str(), "w", stdout);
		make(i);
		fclose(stdout);
		//cerr << ("general.exe < " + in + " > " + out) << endl;
		system(("general.exe < " + in + " > " + out).c_str());
	//	system(("fc " + out +  " " + (string)a + ".out").c_str());
	}
	return 0;
}
