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

const INT maxn = 1e5 + 5;
INT n, m;
std::map<INT, std::string> mapIS;
std::map<std::string, INT> mapSI;
bool direction[maxn];
char name[15];

void run()
{
	n = readIn();
	m = readIn();
	
	for(int i = 0; i < n; i++)
	{
		direction[i] = readIn();
		scanf("%s", name);
		mapIS[i] = name;
		mapSI[name] = i;
	}
	
	INT cnt = 0;
	for(int i = 0; i < m; i++)
	{
		INT isRight = readIn();
		INT count_ = readIn();
		cnt += (isRight == direction[cnt] ? -count_ : count_);
		cnt += n;
		cnt %= n;
	}
	cout << mapIS[cnt] << endl;
}

int main()
{
	run();
	return 0;
}
