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

INT m;
struct BI
{
	static const INT digit = 1e11;
	INT num[1000];
	INT length;

	BI() : num(), length()
	{
	}

	void clear()
	{
		length = 0;
		memset(num, 0, sizeof(num));
	}

	friend std::istream& operator>> (std::istream& in, BI& b)
	{
		const INT pow10[] = {
			1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11
		};
		memset(b.num, 0, sizeof(b.num));
		b.length = 0;

		char buffer[10005];
		scanf("%s", buffer);
		INT len = strlen(buffer);
		bool sign = false;
		for (int i = len - 1, j = 0, k = 0;
			j < len;
			i--, j++)
		{
			sign = true;
			b.num[b.length] += (buffer[i] - '0') * pow10[k];
			k++;
			if (k >= 11)
			{
				k = 0;
				b.length++;
				sign = false;
			}
		}
		if (sign) b.length++;
		return in;
	}

	friend std::ostream& operator<< (std::ostream& out, const BI& b)
	{
		printf("%lld", b.num[b.length - 1]);
		for (int i = b.length - 2; i >= 0; i--)
		{
			printf("%011lld", b.num[i]);
		}
		return out;
	}

	void operator+= (const BI& b)
	{
		length = std::max(length, b.length);
		for (int i = 0; i < length; i++)
		{
			num[i] += b.num[i];
		}
		for (int i = 0; i < length; i++)
		{
			if (num[i] > digit)
			{
				num[i + 1] += num[i] / digit;
				num[i] %= digit;
			}
		}
		if (num[length]) length++;
	}

	void operator>>= (const INT b)
	{
		INT toAnd = (1 << b) - 1;
		INT mod = 0;
		for (int i = length - 1; i >= 0; i--)
		{
			num[i] += mod * digit;
			mod = num[i] & toAnd;
			num[i] >>= b;
		}
		while (length && !num[length - 1]) length--;
	}

	void operator++(int)
	{
		num[0]++;
		INT pos = 0;
		while (num[pos] == digit)
		{
			num[pos + 1]++;
			num[pos] = 0;
		}
		if (num[length]) length++;
	}
} n, ans, temp;

void run()
{
	INT T = readIn();
	while (T--)
	{
		cin >> n;
		m = readIn();
		ans.clear();

		n >>= m - 1;
		temp = n;
		temp++;
		temp >>= 1;
		ans += temp;
		while (n.length)
		{
			n >>= m;
			temp = n;
			temp++;
			temp >>= 1;
			ans += temp;
		}
		cout << ans << endl;
	}
}

int main()
{
	run();
	return 0;
}