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
	scanf("%d",&a);
	return a;
}

const int mod = 1000000007;
const int maxn = 1005;
const int maxm = 205;
int n, m, k;
char A[maxn];
char B[maxm];
int f[2][maxm][maxm];
int s[2][maxm][maxm];

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	scanf("%s%s", A + 1, B + 1);

	s[0][0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		memset(s[i % 2], 0, sizeof(s[i % 2]));
		memset(f[i % 2], 0, sizeof(f[i % 2]));
		s[i % 2][0][0] = 1;
		for(int j = 1; j <= m; j++)
		{
			if(A[i] == B[j])
			{
				for(int c = 1; c <= std::min(j, k); c++)
				{
					f[i % 2][j][c] = (f[(i + 1) % 2][j - 1][c] + s[(i + 1) % 2][j - 1][c - 1]) % mod;
					s[i % 2][j][c] = (s[(i + 1) % 2][j][c] + f[i % 2][j][c]) % mod;
				}
			}
			else
			{
				for(int c = 1; c <= std::min(j, k); c++)
				{
					s[i % 2][j][c] = s[(i + 1) % 2][j][c];
				}
			}
		}
	}
	printf("%d\n", s[n % 2][m][k]);
}

int main()
{
	run();
	return 0;
}
