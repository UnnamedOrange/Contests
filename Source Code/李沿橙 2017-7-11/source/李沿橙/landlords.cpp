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

int n;
int ans;

int card[15];
int cnt[5];

void dfs(int discard = 0)
{
	if(discard > ans) return; //最优性剪枝
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i <= 14; i++) cnt[card[i]]++; //使用这种方式计算不出顺子的情况好算得多
	int noStraight = 0;

	while(cnt[4]) //出炸弹
	{
		cnt[4]--;
		noStraight++;
		if(cnt[2] >= 2) cnt[2]-=2; //四带二对
		else if(cnt[1] >= 2) cnt[1]-=2; //四带二张
	}
	while(cnt[3]) //出三张
	{
		cnt[3]--;
		noStraight++;
		if(cnt[2]) cnt[2]--; //三带二
		else if(cnt[1]) cnt[1]--; //三带一
	}
	if(card[0] && card[1] && cnt[1] >= 2) noStraight--; //Joker是分开存的，但是可以单独打一对出去，在这里校正一下
	noStraight += cnt[1] + cnt[2]; //加上没打的对子和单张牌
	ans = std::min(noStraight + discard,ans); //更新最优解

	for(int i = 3; i <= 14; i++) //从3到A，单顺子
	{
		int j = i;
		for(; card[j] && j <= 14; j++)
		{
			card[j]--;
			if(j - i + 1 >= 5) dfs(discard + 1); //如果多于5张向下搜索
		}
		while(j > i) card[--j]++; //回朔
	}
	for(int i = 3; i <= 14; i++) //双顺子
	{
		int j = i;
		for(; card[j] >= 2 && j <= 14; j++)
		{
			card[j] -= 2;
			if(j - i + 1 >= 3) dfs(discard + 1);
		}
		while(j > i) card[--j] += 2;
	}
	for(int i = 3; i <= 14; i++) //三顺子
	{
		int j = i;
		for(; card[j] >= 3 && j <= 14; j++)
		{
			card[j] -= 3;
			if(j - i + 1 >= 2) dfs(discard + 1);
		}
		while(j > i) card[--j] += 3;
	}
}
int main()
{
	int a = readIn();
	n = readIn();
	while (a--)
	{
		ans = n;
		memset(card, 0, sizeof(card));
		for(int i = 1; i <= n; ++i)
		{
			int x=readIn();
			int y=readIn();
			if(!x) card[y - 1]++; //Joker分别放在0和1，因为在顺子中不能带Joker
			else if(x == 1) card[14]++; //A放在14的位置，因为顺子的顺序是JQKA，刚好连上
			else card[x]++; //其它的正常存
		}
		dfs();
		printf("%d\n",ans);
	}
	return 0;
}
