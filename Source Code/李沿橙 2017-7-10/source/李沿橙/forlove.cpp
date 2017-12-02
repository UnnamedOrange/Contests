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
	scanf("%d", &a);
	return a;
}

const int maxn = 10005;
const char* szAns[] =
{
	"You still have a chance.",
	"You are destined to be single."
};
int n;
int sequeue[maxn];
int temp[maxn];
int pair;

void mergeSort(int l = 0, int r = n)
{
	if (r - l == 1) return;
	int mid = (l + r) / 2;
	mergeSort(l, mid);
	mergeSort(mid, r);
	int i = l;
	int j = mid;
	int k = l;
	while (i < mid || j < r)
	{
		if (j >= r || i < mid && sequeue[i] < sequeue[j])
		{
			temp[k++] = sequeue[i++];
		}
		else
		{
			temp[k++] = sequeue[j++];
			pair += mid - i;
		}
	}
	for (int i = l; i < r; i++)
	{
		sequeue[i] = temp[i];
	}
}

void run()
{
	int a = readIn();
	while (a--)
	{
		n = readIn();
		int to = n * n;
		int cnt = 0;
		pair = 0;
		for (int i = 1; i <= to; i++)
		{
			sequeue[cnt] = readIn();
			if (sequeue[cnt]) cnt++;
		}

		mergeSort(0, cnt);
		printf("%s\n", szAns[pair & 1]);
	}
}

int main()
{
	run();
	return 0;
}
