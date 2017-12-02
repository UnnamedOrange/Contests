#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const int maxn = 105;
char mapped[maxn];
char origin[maxn];
char message[maxn];
int cMap[26];
int cMapT[26];
int count_;

int main()
{
	memset(cMap, -1, sizeof(cMap));
	memset(cMapT, -1, sizeof(cMapT));
	scanf("%s", mapped);
	scanf("%s", origin);
	scanf("%s", message);
	int keyLength = strlen(mapped);
	int msgLength = strlen(message);
	bool bOk = true;
	for (int i = 0; i < keyLength; i++)
	{
		int chKey = mapped[i];
		int chOrigin = origin[i];
		if (cMap[chKey - 'A'] == -1 && cMapT[chOrigin - 'A'] == -1)
		{
			count_++;
			cMap[chKey - 'A'] = chOrigin;
			cMapT[chOrigin - 'A'] = chKey;
		}
		else if (cMap[chKey - 'A'] == -1 || cMapT[chOrigin - 'A'] == -1)
		{
			bOk = false;
			break;
		}
		else if (cMap[chKey - 'A'] != chOrigin || cMapT[chOrigin - 'A'] != chKey)
		{
			bOk = false;
			break;
		}
	}
	if (!bOk || count_ != 26)
	{
		printf("Failed\n");
		return 0;
	}

	for (int i = 0; i < msgLength; i++)
	{
		printf("%c", cMap[message[i] - 'A']);
	}
	puts("");
	return 0;
}