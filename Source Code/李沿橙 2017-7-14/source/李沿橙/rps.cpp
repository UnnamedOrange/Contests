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
typedef int INT;
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

const int maxn = 205;
int n;
int nA;
int nB;
int sA[maxn];
int sB[maxn];
INT rA = 0, rB = 0;

const int table[5][5] =
{
	{ 0, 0, 1, 1, 0 },
	{ 1, 0, 0, 1, 0 },
	{ 0, 1, 0, 0, 1 },
	{ 0, 0, 1, 0, 1 },
	{ 1, 1, 0, 0, 0 }
};

void run()
{
	n = readIn();
	nA = readIn();
	nB = readIn();
	for(int i = 0; i < nA; i++)
	{
		sA[i] = readIn();
	}
	for(int i = 0; i < nB; i++)
	{
		sB[i] = readIn();
	}

	int sequenceA = 0;
	int sequenceB = 0;
	for(int i = 0; i < n; i++)
	{
		int& A = sA[sequenceA];
		int& B = sB[sequenceB];
		rA += table[A][B];
		rB += table[B][A];
		sequenceA++;
		sequenceA %= nA;
		sequenceB++;
		sequenceB %= nB;
	}
	cout << rA << " " << rB << endl;
}

int main()
{
	run();
	return 0;
}
