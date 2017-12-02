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

const INT maxn = 105;
INT n, m;

std::vector<std::string> library;
void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= n; i++)
	{
		char buffer[105];
		scanf("%s", buffer);
		library.push_back(buffer);
	}
	while(m--)
	{
		INT ins = readIn();
		if(ins == 1)
		{
			char buffer[105];
			scanf("%s", buffer);
			library.push_back(buffer);
		}
		else if(ins == 2)
		{
			INT num = readIn();
			std::vector<INT> Index;
			INT minLength = 105;
			for(int i = 1; i <= num; i++)
			{
				Index.push_back(readIn() - 1);
				minLength = std::min(minLength, INT(library[Index.back()].length()));
			}

			INT ans = minLength;
			for(int i = 0; i < minLength; i++)
			{
				const std::string& s1 = library[Index[0]];
				char ch = s1[s1.length() - 1 - i];
				bool bOk = true;
				for(int j = 1; j < Index.size(); j++)
				{
					const std::string& s = library[Index[j]];
					if(s[s.length() - 1 - i] != ch)
					{
						bOk = false;
						break;
					}
				}
				if(!bOk)
				{
					ans = i;
					break;
				}
			}
			cout << ans << endl;
		}
	}
}

int main()
{
#ifndef JUDGE
	freopen("biology.in", "r", stdin);
	freopen("biology.out", "w", stdout);
#endif
	run();
	return 0;
}
