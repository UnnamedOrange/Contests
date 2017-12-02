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
#define FOR(x, f, t) for(int x = (f); x <= (t); x++)
inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

int lengthKey;
int lengthC;
char key[105];
char C[1005]; //注意是输入的密文

const int NONE = 0;
const int UPPER = 1;
const int LOWER = 2;
inline int chType(char ch)
{
	if(ch>='A' && ch<='Z') return UPPER;
	else if(ch>='a' && ch<='z') return LOWER;
	return NONE;
}

char RT(char chC, char chKey) //R的逆运算
{
	int sub = 0;
	if(chType(chKey)==UPPER)
	{
		sub=chKey - 'A';
	}
	else if(chType(chKey)==LOWER)
	{
		sub=chKey - 'a';
	}
	//else //不存在，数据保证有效

	int type = chType(chC);
	char cRet = chC - sub;
	if(chType(cRet) != type)
	{
		cRet+=26;
	}
	return cRet;
}

void run()
{
	scanf("%s",key);
	scanf("%s",C);
	lengthKey = strlen(key);
	lengthC = strlen(C);
	int routine = 0;
	for(int i=0; i<lengthC; i++)
	{
		printf("%c", RT(C[i], key[routine]));
		routine++;
		if(routine>=lengthKey) routine=0;
	}
	puts("");
}

int main()
{
	run();
	return 0;
}
