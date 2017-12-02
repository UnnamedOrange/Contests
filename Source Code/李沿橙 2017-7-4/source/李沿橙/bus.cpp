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

const int maxn = 1005;
const int maxm = 10005;
int n, m, k;
int d[maxn];
int start[maxm];
int from[maxm];
int to[maxm];
int earliest[maxn]; //ÿ��������ĳ���ʱ�䣨����˿͵ĵ���ʱ�䣩
int arrival[maxn];
int getOff[maxn];

void run()
{
	n = readIn();
	m = readIn();
	k = readIn();
	for (int i = 1; i <= n - 1; i++)
	{
		d[i] = readIn();
	}
	for (int i = 1; i <= m; i++)
	{
		start[i] = readIn();
		from[i] = readIn();
		to[i] = readIn();
		earliest[from[i]] = std::max(earliest[from[i]], start[i]);
		getOff[to[i]]++;
	}
	for (int i = 2; i <= n; i++)
	{
		arrival[i] = std::max(arrival[i - 1], earliest[i - 1]) + d[i - 1];
	}

	while (k--)
	{
		int sum = 0;
		int maxi = 0;
		int maxindex = 0;
		for (int i = n; i >= 2; i--) //����Ҫ����������˵ȳ���ǰһ��·����˵���ͳ�� 
		{
			if (earliest[i] >= arrival[i]) //�����ˣ����� 
				sum = 0;
			sum += getOff[i]; //���ݷ�����Ӧ�ú�д������ 
			if (d[i - 1] > 0 && sum > maxi)
			{
				maxi = sum;
				maxindex = i - 1;
			}
		}
		if (!maxindex) break; //û���κ�һ��·���Լ��� 
		d[maxindex]--;
		for (int i = 2; i <= n; i++) //ά�� 
		{
			arrival[i] = std::max(arrival[i - 1], earliest[i - 1]) + d[i - 1];
		}
	}

	for (int i = 2; i <= n; i++)
	{
		arrival[i] = std::max(arrival[i - 1], earliest[i - 1]) + d[i - 1];
	}
	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		ans += arrival[to[i]] - start[i];
	}
	printf("%d", ans);
}

int main()
{
	run();
	return 0;
}
