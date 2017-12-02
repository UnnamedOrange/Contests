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

int n;
int a0, a1, b0, b1;

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a%b);
}

int main()
{
	n = readIn();
	while (n--)
	{
		a0 = readIn();
		a1 = readIn();
		b0 = readIn();
		b1 = readIn();

		//��lcm(x,b0) == b1
		//��x*b0/gcd(x,b0) == b1
		//��x == gcd(x,b0)*b1/b0
		//��gcd(x,b0)|b0
		//ö��b0������������ʱ�临�Ӷ�ΪO(b0^(1/2))����һ���ϴ������Ϊb0���Խ�С������
		//��������֤gcd(x,a0) == a1, lcm(x,b0) == b1
		//ע������������ 

		int ans = 0;
		int base = b1 / b0;
		int B0 = b0;
		int to = sqrt(b0);
		for (int i = 1; i <= to; i++)
		{
			if (b0 % i) continue;
			int x = base*i;
			if (gcd(x, a0) == a1 && x / gcd(x, b0)*b0 == b1)
				ans++;
			if (base*(b0 / i) != x) //ע�����������أ������˾�ֻ��60�� 
			{
				x = base*(b0 / i);
				if (gcd(x, a0) == a1 && x / gcd(x, b0)*b0 == b1)
					ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}