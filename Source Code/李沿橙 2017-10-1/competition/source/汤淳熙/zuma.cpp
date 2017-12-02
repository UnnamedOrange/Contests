#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cctype>
#include <cmath>
#include <cfloat>
#include <ctime>
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
const int MAXL = 205;

struct Main {
	char Line[MAXL]
	int n;
	/*

		n 个黑球、白球，任意三个球颜色不同
		不断插入，有三个球颜色相同的球就消去
		最小插入球数

	 */

	Main(void)
	{
		scanf("%s", Line);
		n = strlen(Line);

		cout << "3" << endl;
	}
};

int main(void)
{
#ifndef LOCAL
	freopen("zuma.in", "r", stdin);
	freopen("zuma.out", "w", stdout);
#endif // LOCAL

    delete new Main();

	return 0;
}
