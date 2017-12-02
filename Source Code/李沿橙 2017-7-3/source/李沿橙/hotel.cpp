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

const int maxn = 55;
int n, k, p;

void run()
{
	n = readIn();
	k = readIn();
	p = readIn();

	int bestPos = 0; //���ȵ�Ӧ�������ң����濧�ȵ����ѵ�ַ
	int times[maxn] = { 0 }; //����ͬɫ��ջ���ֵĴ���
	int lastAppear[maxn] = { 0 }; //����ĳ����ɫ��ջ��һ�γ��ֵ�λ��
	int availableTimes[maxn] = { 0 }; //����ĳ����ɫ��ջ���γ�һ�Եĸ���
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int style = readIn();
		int cost = readIn();
		if (cost <= p)
		{
			bestPos = i; //ά�����ȵ�λ��
		}

		if (bestPos >= lastAppear[style]) //��bestPos����һ�������ɫ�Ŀ�ջ��Ҫ����һ�㣬�Ϳ��Ա�֤��times[style]����ջ�����(��ʱtimes��û�и���)
			availableTimes[style] = times[style];

		lastAppear[style] = i; //ά����һ�γ��ֵ�λ��
		times[style]++; //ά�����ֵĴ���
		ans += availableTimes[style]; //�����
	}
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
