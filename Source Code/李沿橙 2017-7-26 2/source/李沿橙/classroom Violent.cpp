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
	while(!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if(ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if(minus) a = -a;
	return a;
}

const INT maxn = 2005;
const INT maxv = 305;
INT n, m, v, e;
INT c[maxn];
INT d[maxn];
double posibility[maxn];
INT rect[maxv][maxv];
INT INF;
bool special = true;

void work3()
{
	double ans = 1e100;
	INT U = 1 << n;
	for(int S = 0; S < U; S++)
	{
		INT count1 = 0;
		for(int i = 0; i < n; i++)
		{
			if((1 << i) & S) count1++;
		}
		if(count1 > m) continue;
		
		INT cnt = S & 1 ? d[0] : c[0];
		INT dis = 0;
		for(int i = 1; i < n; i++)
		{
			if(S & (1 << i))
			{
				dis += rect[cnt][d[i]];
				cnt = d[i];
			}
			else
			{
				dis += rect[cnt][c[i]];
				cnt = c[i];
			}
		}
		ans = std::min(ans, double(cnt));
	}
	printf("%.2f\n", ans);
}

void work2()
{
	if(m == 0)
	{
		INT cnt = c[0];
		INT dis = 0;
		for(int i = 1; i < n; i++)
		{
			dis += rect[cnt][c[i]];
			cnt = c[i];
		}
		printf("%.2f\n", double(dis));
	}
	else if(m == 1)
	{
		double ans = 1e100;
		for(int i = 0; i < n; i++)
		{
			INT dis1 = 0;
			INT dis2 = 0;
			INT cnt = i ? c[0] : d[0];
			for(int j = 1; j < n; j++)
			{
				dis1 += rect[cnt][i == j ? d[j] : c[j]];
				cnt = i == j ? d[j] : c[j];
			}
			cnt = c[0];
			for(int j = 1; j < n; j++)
			{
				dis2 += rect[cnt][c[j]];
				cnt = c[j];
			}
			ans = std::min(ans, posibility[i] * dis1 + (1 - posibility[i]) * dis2);
		}
		printf("%.2f\n", ans);
	}
}

void work()
{
	double ans = 1e100;
	INT U = 1 << n;
	for(int S = 0; S < U; S++)
	{
		INT count1 = 0;
		for(int i = 0; i < n; i++)
		{
			if((1 << i) & S) count1++;
		}
		if(count1 > m) continue;
		
		double temp = 0;
		for(int S0 = S; ; S0 = (S0 - 1) & S)
		{
			double posi = S0 & 1 ? posibility[0] : (1 - posibility[0]);
			if(!(S & 1)) posi = 1;
			INT cnt = S0 & 1 ? d[0] : c[0];
			INT dis = 0;
			for(int i = 1; i < n; i++)
			{
				if(S0 & (1 << i))
				{
					dis += rect[cnt][d[i]];
					cnt = d[i];
				}
				else
				{
					dis += rect[cnt][c[i]];
					cnt = c[i];
				}
				if(S & (1 << i))
				{
					posi *= S0 & (1 << i) ? posibility[i] : (1 - posibility[i]);
				}
			}
			//cout << dis << endl;
			temp += posi * dis;
			if(!S0) break;
		}
		//cout << temp << endl;
		ans = std::min(ans, temp);
	}
	printf("%.2f\n", ans);
}

void initFloyd()
{
	memset(&INF, 0x3f, sizeof(INT));
	memset(rect, 0x3f, sizeof(rect));
	for(int i = 1; i <= v; i++)
	{
		rect[i][i] = 0;
	}
	for(int i = 1; i <= e; i++)
	{
		INT from = readIn();
		INT to = readIn();
		INT weight = readIn();
		rect[from][to] = std::min(rect[from][to], weight);
		rect[to][from] = std::min(rect[to][from], weight);
	}
	for(int k = 1; k <= v; k++)
	{
		for(int i = 1; i <= v; i++)
		{
			for(int j = 1; j <= v; j++)
			{
				if(i != k && i != j && j != k)
					rect[i][j] = std::min(rect[i][j], rect[i][k] + rect[k][j]);
			}
		}
	}
}

void initRoom()
{
	for(int i = 0; i < n; i++)
	{
		c[i] = readIn();
	}
	for(int i = 0; i < n; i++)
	{
		d[i] = readIn();
	}
	for(int i = 0; i < n; i++)
	{
		scanf("%lf", &posibility[i]);
		if(posibility[i] != 1) special = false;
	}
}

void run()
{
	n = readIn();
	m = readIn();
	v = readIn();
	e = readIn();
	initRoom();
	initFloyd();
	
	if(n <= 1)
	{
		puts("0.00");
		return;
	}

	if(m <= 1)
	{
		work2();
	}
	else if(n <= 15 && m)
	{
		work();
	}
	else if(special)
	{
		work3();
	}
}

int main()
{
	freopen("classroom.in", "r", stdin);
	freopen("classroom.out", "w", stdout);
	run();
}
