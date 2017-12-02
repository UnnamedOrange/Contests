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
using std::cin;
using std::cout;
using std::endl;
inline int readIn()
{
	int a;
	scanf("%d", &a);
	return a;
}

const char* szAns[] =
{
	"NO",
	"YES"
};
const int maxn = 105;
char secret[maxn];
char origin[maxn];
int timesOrigin[26];
int timesSecret[26];

void run()
{
	scanf("%s", secret);
	scanf("%s", origin);
	int length = strlen(origin);
	if(strlen(secret) != length)
	{
		printf("%s\n", szAns[0]);
		return;
	}

	for(int i = 0; i < length; i++)
	{
		timesOrigin[origin[i] - 'A']++;
		timesSecret[secret[i] - 'A']++;
	}
	std::sort(timesOrigin, timesOrigin + 26);
	std::sort(timesSecret, timesSecret + 26);
	for(int i = 0; i < 26; i++)
	{
		if(timesOrigin[i] != timesSecret[i])
		{
			printf("%s\n",szAns[0]);
			return;
		}
	}
	printf("%s\n",szAns[1]);
}

int main()
{
	run();
	return 0;
}
