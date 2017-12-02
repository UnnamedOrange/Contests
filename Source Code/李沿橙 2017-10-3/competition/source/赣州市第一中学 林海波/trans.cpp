#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 1000010;

using namespace std;

int n, k;
char ch;
int flag = 0;
int a[maxn];

inline bool judge(int i);
inline bool change(int i);

int main()
{
	freopen("trans.in", "r", stdin);
	freopen("trans.out", "w", stdout);
	while (cin >> n >> k)
	{
		for (int i = 1; i <= n; i++)
		{
			cin >> ch;
			a[i] = ch - '0';
		}
		int j = 0;
		for (int i = 1; i <= n && j < k; i++)
			if (judge(i))
			{
				j++;
				if (change(i))
					i -= 2;
				else if (flag == i + 1)
					if ((k - j) % 2 == 1)
						j = k - 1;
					else
						j = k;
			}
		for (int i = 1; i <= n; i++)
			cout << a[i];
		cout << endl;
	}
	return 0;
}

inline bool judge(int i)
{
	return a[i] == 2 && a[i + 1] == 3;
}

inline bool change(int i)
{
	if (i % 2 == 1)
	{
		a[i + 1] = 2;
		return false;
	}
	else
	{
		a[i] = 3;
		return true;
	}
}

