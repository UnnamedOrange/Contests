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
	bool minus = false;
	INT a = 0;
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

const INT maxn = 35;
INT n, m, q;
bool board[maxn][maxn];
INT ans;
INT tx, ty;

const INT vecx[] = { 1, -1, 0, 0 };
const INT vecy[] = { 0, 0, 1, -1 };
bool hashTable[1000000];
struct status
{
	INT ex, ey, sx, sy;
	INT length;
	status(INT ex = 0, INT ey = 0,
	       INT sx = 0, INT sy = 0,
	       INT length = 0):
		ex(ex), ey(ey), sx(sx), sy(sy),
		length(length)
	{
	}

	INT hashVal()
	{
		const INT b1 = 31;
		const INT b2 = b1 * 31;
		const INT b3 = b2 * 31;
		return ex + b1 * ey + b2 * sx + b3 * sy;
	}
} origin;
void bfs()
{
	if(origin.sx == tx && origin.sy == ty)
	{
		ans = 0;
		return;
	}
	ans = -1;
	memset(hashTable, 0, sizeof(hashTable));
	std::queue<status> q;
	q.push(origin);
	hashTable[origin.hashVal()] = true;

	while(!q.empty())
	{
		status from = q.front();
		q.pop();
		for(int i = 0; i < 4; i++)
		{
			INT newx = from.ex + vecx[i];
			INT newy = from.ey + vecy[i];
			if(newx <= 0 || newx > n) continue;
			if(newy <= 0 || newy > m) continue;
			if(!board[newx][newy]) continue;
			INT sx = from.sx;
			INT sy = from.sy;
			if(newx == sx && newy == sy)
			{
				sx = from.ex;
				sy = from.ey;
			}
			status to(newx, newy, sx, sy, from.length + 1);
			INT hashVal = to.hashVal();
			if(!hashTable[hashVal])
			{
				q.push(to);
				hashTable[hashVal] = true;
				if(to.sx == tx && to.sy == ty)
				{
					ans = to.length;
					return;
				}
			}
		}
	}
}

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			board[i][j] = readIn();
		}
	}
	while(q--)
	{
		origin.ex = readIn();
		origin.ey = readIn();
		origin.sx = readIn();
		origin.sy = readIn();
		tx = readIn();
		ty = readIn();
		bfs();
		cout << ans << endl;
	}
}

int main()
{
	run();
	return 0;
}
