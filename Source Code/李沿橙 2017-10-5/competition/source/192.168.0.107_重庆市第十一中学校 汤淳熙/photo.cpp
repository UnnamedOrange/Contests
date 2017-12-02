#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <bitset>
#include <set>
#include <map>
using namespace std;
const int MAXN = 1005;
const long long MOD = 1e9 + 7;

/*

图片像素点 m * n，每一个点都有颜色，共 k 种

分界线，分成左右两半，左右两半颜色总数相同

 */


struct Brute {
	int n, m, k;

	Brute(void) {
		scanf("%d %d %d", &n, &m, &k);

		cout << n * m * k % MOD << endl;
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("photo.in", "r", stdin);
	freopen("photo.out", "w", stdout);
#endif // LOCAL

	delete new Brute();

	return 0;
}
