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

const INT INF = 10000;
const INT maxn = 205;
char buffer[maxn];
INT n = 1;
INT seq[maxn];

#define RunInstance(x) delete new x
struct cheat1
{
	std::map<std::vector<INT>, INT> m;

	INT search(std::vector<INT> origin = std::vector<INT> (seq + 1, seq + 1 + n))
	{
		if(m.count(origin)) return m[origin];
		if(!origin.size())
		{
			return 0;
		}
		INT ret = INF;
		for(int i = 0; i < origin.size(); i++)
		{
			INT l = i - 1, r = i + 1;
			while(l >= 0 && r < origin.size() && origin[l] + origin[r] >= 3)
			{
				l--;
				r++;
			}
			std::vector<INT> temp;

			bool sign = l >= 0 && r < origin.size();
			for(int j = 0; j <= l - sign; j++)
			{
				temp.push_back(origin[j]);
			}
			if(sign) temp.push_back(origin[l] + origin[r]);
			for(int j = r + sign; j < origin.size(); j++)
			{
				temp.push_back(origin[j]);
			}
			ret = std::min(ret, (origin[i] == 1 ? 2 : 1) + search(temp));
		}
		return m[origin] = ret;
	}

	cheat1()
	{
		cout << search() << endl;
	}
};
struct work : public cheat1
{
};

void run()
{
	scanf("%s", buffer);
	INT length = strlen(buffer);
	for(int i = 0; i < length; i++)
	{
		if(i && buffer[i] != buffer[i - 1]) n++;
		seq[n]++;
	}
	if(n <= 20) RunInstance(cheat1);
	else RunInstance(work);
}

int main()
{
#ifndef JUDGE
	freopen("zuma.in", "r", stdin);
	freopen("zuma.out", "w", stdout);
#endif
	run();
	return 0;
}
