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

const INT maxn = 100005;
INT n;
INT seq[maxn];
bool isWdf(INT x)
{
	if(!x) return false;
	while(x)
	{
		if(x % 10 != 4 && x % 10 != 7) return false;
		x /= 10;
	}
	return true;
}

INT ans;
void divide(INT l = 1, INT r = n)
{
	if(r - l <= 0) return;
	else if(r - l == 1)
	{
		if(!isWdf(seq[l]) || seq[l] != seq[r]) ans++;
		return;
	}
	INT mid = (l + r) >> 1;
	divide(l, mid);
	divide(mid + 1, r);

	INT midL, midR, L, R, cnt, t1, t2;
	{
		std::map<INT, INT> wdfM;
		midL = mid;
		midR = mid + 1;
		for(; midL >= l; midL--)
		{
			if(isWdf(seq[midL]))
			{
				if(wdfM[seq[midL]]) break;
				else wdfM[seq[midL]]++;
			}
		}
		midL++;

		for(; midR <= r; midR++)
		{
			if(isWdf(seq[midR]))
			{
				if(wdfM[seq[midR]]) break;
				else wdfM[seq[midR]]++;
			}
		}
		midR--;

		std::map<INT, INT> wdfM2;
		cnt = 0;
		L = R = l;
		for(; R < midL; R++)
		{
			if(isWdf(seq[R]))
			{
				while(wdfM2[seq[R]])
				{
					if(isWdf(seq[L])) wdfM2[seq[L]]--;
					L++;
				}
				wdfM2[seq[R]]++;
			}
			cnt += R - L + 1;
		}
		R--;
		ans += cnt * (midR - mid);

		for(; midL < mid; midL++)
		{
			if(isWdf(seq[midL]))
			{
				wdfM[seq[midL]]--;
				for(; midR <= r; midR++)
				{
					if(isWdf(seq[midR]))
					{
						if(wdfM[seq[midR]]) break;
						else wdfM[seq[midR]]++;
					}
				}
				midR--;
			}
			R++;
			if(isWdf(seq[R]))
			{
				while(wdfM2[seq[R]])
				{
					if(isWdf(seq[L])) wdfM2[seq[L]]--;
					L++;
				}
				wdfM2[seq[R]]++;
			}
			cnt += R - L + 1;
			ans += cnt * (midR - mid);
		}
		R++;
		if(isWdf(seq[R]))
		{
			while(wdfM2[seq[R]])
			{
				if(isWdf(seq[L])) wdfM2[seq[L]]--;
				L++;
			}
			wdfM2[seq[R]]++;
		}
		cnt += R - L + 1;
		t1 = cnt;
	}
	{
		std::map<INT, INT> wdfM;
		midL = mid;
		midR = mid + 1;
		for(; midR <= r; midR++)
		{
			if(isWdf(seq[midR]))
			{
				if(wdfM[seq[midR]]) break;
				else wdfM[seq[midR]]++;
			}
		}
		midR--;

		for(; midL >= l; midL--)
		{
			if(isWdf(seq[midL]))
			{
				if(wdfM[seq[midL]]) break;
				else wdfM[seq[midL]]++;
			}
		}
		midL++;

		std::map<INT, INT> wdfM2;
		cnt = 0;
		L = R = r;
		for(; L > midR; L--)
		{
			if(isWdf(seq[L]))
			{
				while(wdfM2[seq[L]])
				{
					if(isWdf(seq[R])) wdfM2[seq[R]]--;
					R--;
				}
				wdfM2[seq[L]]++;
			}
			cnt += R - L + 1;
		}
		L++;
		ans += cnt * (mid - midL + 1);

		for(; midR > mid + 1; midR--)
		{
			if(isWdf(seq[midR]))
			{
				wdfM[seq[midR]]--;
				for(; midL >= l; midL--)
				{
					if(isWdf(seq[midL]))
					{
						if(wdfM[seq[midL]]) break;
						else wdfM[seq[midL]]++;
					}
				}
				midL++;
			}
			L--;
			if(isWdf(seq[L]))
			{
				while(wdfM2[seq[L]])
				{
					if(isWdf(seq[R])) wdfM2[seq[R]]--;
					R--;
				}
				wdfM2[seq[L]]++;
			}
			cnt += R - L + 1;
			ans += cnt * (midR - mid);
		}
		L--;
		if(isWdf(seq[L]))
		{
			while(wdfM2[seq[L]])
			{
				if(isWdf(seq[R])) wdfM2[seq[R]]--;
				R--;
			}
			wdfM2[seq[L]]++;
		}
		t2 = R - L + 1;
	}
	ans += t1 * t2;
}

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		seq[i] = readIn();
	}
	divide();
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
