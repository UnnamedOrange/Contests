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
	INT a;
	scanf("%d", &a);
	return a;
}

const INT mod = 1e7 + 7;
const INT maxn = 1005;
INT n, m;
INT num[maxn];
INT sum[maxn];
INT f[maxn][maxn];

void run()
{
	n = readIn();
	m = readIn();
	for(int i = 1; i <= n; i++)
	{
		num[i] = readIn();
	}
	std::sort(num + 1, num + 1 + n, std::greater<INT>());
	for(int i = 1; i <= n; i++)
	{
		sum[i] = sum[i - 1] + num[i];
	}

	INT ans = -1;
	f[0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		//��ѡ����С��ֵΪnum[i]
		for(int j = std::max(0, m - (sum[n] - sum[i - 1]) + 1); //���ող���ѡnum[i]
		        j <= m - (sum[n] - sum[i]); //�Ӱ�����С��num[i]��ѡ��
		        j++)
		{
			ans = (ans + f[i - 1][j]) % mod;
		}
		for(int j = m; j >= 0; j--)
		{
			//01������������
			f[i][j] = f[i - 1][j]; //��ѡ
			f[i][j] %= mod;
			if(j - num[i] >= 0) //ѡ
			{
				f[i][j] += f[i - 1][j - num[i]];
				f[i][j] %= mod;
			}
		}
	}
	if(ans == -1) ans = 1; //���У�һ��������ѡ������һ�ַ���
	else ans = (ans + 1) % mod;
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
