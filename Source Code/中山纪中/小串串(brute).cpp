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
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = 100005;
char buffer[maxn];
INT length;

void run()
{
	INT T = readIn();
	while (T--)
	{
		scanf("%s", buffer + 1);
		length = strlen(buffer + 1);
		std::map<std::string, INT> mapSI;
		for (int i = 1; i <= length; i++)
		{
			for (int j = i; j <= length; j++)
			{
				mapSI[std::string(&buffer[i], &buffer[j] + 1)]++;
			}
		}
		long long ans = 0;
		std::map<std::string, INT>::iterator it;
		for (it = mapSI.begin(); it != mapSI.end(); it++)
		{
			ans += it->second * it->second;
		}
		cout << ans << endl;
	}
}

int main()
{
	run();
	return 0;
}
