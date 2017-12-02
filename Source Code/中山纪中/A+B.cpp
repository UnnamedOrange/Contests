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

const INT maxn = 2000005;
INT n;
INT A[maxn], lengthA;

void run()
{
	for (int i = 0; i < 2; i++)
	{
		n = readIn();
		lengthA = std::max(lengthA, n);
		for (int i = 1; i <= n; i++)
		{
			A[i] += readIn();
		}
	}
	bool sign = false;
	do
	{
		sign = false;
		//deal with 1 and 2
		INT carry3 = std::min(A[1], A[2]);
		A[1] -= carry3;
		A[2] -= carry3;
		A[3] += carry3;

		if (A[1])
		{
			A[3] += A[1] / 3;
			A[1] %= 3;
			if (A[1] == 2)
			{
				A[2]++;
				A[1] = 0;
			}
		}
		else if (A[2])
		{
			A[3] += A[2] / 3 * 2;
			A[2] %= 3;
			if (A[2] == 2)
			{
				A[1]++;
				A[3]++;
				A[2] = 0;
			}
		}

		for (int i = 3; i <= lengthA + 1; i++)
		{
			if (A[i - 1] && A[i - 2])
			{
				sign = true;
				INT carry = std::min(A[i - 1], A[i - 2]);
				A[i] += carry;
				A[i - 1] -= carry;
				A[i - 2] -= carry;
			}
			if (A[i] > 1)
			{
				sign = true;
				A[i - 2] += A[i] >> 1;
				A[i + 1] += A[i] >> 1;
				A[i] &= 1;
			}
			if (A[i + 1] && i + 1 > lengthA) lengthA = i + 1;
			else if (A[i] && i > lengthA) lengthA = i;
		}
	} while (sign);

	while (lengthA && !A[lengthA]) lengthA--;
	printf("%d", lengthA); //notice that INT is int in this problem
	for (int i = 1; i <= lengthA; i++)
	{
		printf(" %d", A[i]);
	}
}

int main()
{
	run();
	return 0;
}
