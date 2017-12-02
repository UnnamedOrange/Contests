#include <bits/stdc++.h>
using namespace std;

map<int, bool> ext;
int a[1000000];
priority_queue<pair<int, int> > H;

#define rd abs(rand() * rand())

void makeData(int number) {
	freopen("number", "w", stdout);
	printf("%d\n", number);
	fclose(stdout);
	char input[10];
	sprintf(input, "marriage%d.in", number);
	freopen(input, "w", stdout);

	if (number < 6)
		printf("%d\n", 500 + rd % 500 + 1);

	else
		printf("%d\n", 5000000 + rd % 5000000 + 1);

	fclose(stdout);
	system("std.exe");
}

int main() {
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
		makeData(i);
	return 0;
}
