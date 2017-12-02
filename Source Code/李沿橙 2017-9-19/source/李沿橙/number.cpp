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

const INT maxn = 200005;
INT n, m, k;
INT A[maxn], B[maxn];

#define RunInstance(x) delete new x
struct work
{
	bool check(INT s)
	{
		INT count_ = 0;
		INT pos2 = m;
		for(int i = 1; i <= n; i++)
		{
			while(pos2 && A[i] * B[pos2] > s) pos2--;
			if(!pos2) break;
			count_ += pos2;
		}
		//count_：有多少个小于等于s的 
		return count_ < k;
	}

	work()
	{
		std::sort(A + 1, A + 1 + n);
		std::sort(B + 1, B + 1 + m);
		INT l = A[1] * B[1] - 1, r = A[n] * B[m];
		while(r - l > 1)
		{
			INT mid = l + ((r - l) >> 1);
			if(check(mid))
			{
				l = mid;
			}
			else
			{
				r = mid;
			}
		}
		cout << r << endl;
	}
};
struct cheat
{
	cheat()
	{
		std::vector<INT> vec;
		vec.reserve(n * m + 1);
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				vec.push_back(A[i] * B[j]);
			}
		}
		std::nth_element(vec.begin(), vec.begin() + k - 1, vec.end());
		cout << vec[k - 1] << endl;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for(int i = 1; i <= n; i++)
	{
		A[i] = readIn();
	}
	for(int i = 1; i <= m; i++)
	{
		B[i] = readIn();
	}

//	if(n * m <= 100000)
//		RunInstance(cheat);
//	else
		RunInstance(work);
}

int main()
{
	run();
	return 0;
}
