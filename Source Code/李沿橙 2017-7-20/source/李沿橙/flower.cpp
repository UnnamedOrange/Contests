#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
typedef long long INT;
inline INT readIn()
{
	bool minus = false;
	INT a = 0;
	char ch = getchar();
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT maxn = 100005;
INT n;
INT N;
INT height[maxn];
INT ans;

void run()
{
	n = readIn();
	ans = 1;

	INT pre = -1;
	for(int i = 1; i <= n; i++)
	{
		INT input = readIn();
		if(input == pre) continue;
		height[++N] = input;
		pre = input;
	}

	if(N >= 2) ans++; //如果长度大于等于2的话就有两个端点
	for(int i = 2; i <= N - 1; i++)
	{
		if(height[i - 1] < height[i] && height[i] > height[i + 1]) ans++;
		else if(height[i - 1] > height[i] && height[i] < height[i + 1]) ans++;
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
