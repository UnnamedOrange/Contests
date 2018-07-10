#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

const int CASE = 7;
const int LimK[CASE] = {4, 10, 14, 50, 300, 2000, 30000};
const int LimN[CASE] = {3, 9, 10, 40, 150, 700, 15000};

int main() {

	srand(time(0));

	For(i, 1, CASE) {
		
		char cmd[100];
		sprintf(cmd, "or%d.in", i);
		freopen(cmd, "w", stdout);

		int k = LimK[i - 1];
		k -= rand() % k / 10;

		int n = LimN[i - 1];
		n -= rand() % n / 10;

		printf("%d %d\n", n, k);

		sprintf(cmd, "time ./or < or%d.in > or%d.out", i, i);
		freopen("tmp", "w", stdout);
		system(cmd);

	}

	return 0;
}
