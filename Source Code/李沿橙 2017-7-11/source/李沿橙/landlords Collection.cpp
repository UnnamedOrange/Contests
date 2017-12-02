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

int cnt[5],card[16];

void dfs(int discard = 0)
{
	if(discard > ans) return; //最优性剪枝
	int times = 0;
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i <= 14; i++) cnt[card[i]]++;

	while(cnt[4])
	{
		cnt[4]--;
		times++;                //炸弹
		if(cnt[2] >= 2) cnt[2]-=2;         //能不能带二
		else if(cnt[1] >= 2)cnt[1]-=2;
	}
	for(; cnt[3];)
	{
		cnt[3]--;
		times++;                //三张牌
		if(cnt[2]) cnt[2]--;             //能不能带一
		else if(cnt[1]) cnt[1]--;
	}                  //我在思考把三带一和四带二写成子程序是不是更简洁？
	if(card[0] && card[1] && cnt[1]>=2) times--;     //看看剩下的单牌有没有王炸
	times += cnt[1] + cnt[2];
	ans = std::min(times + discard,ans);

	for(int i = 3, j; i < 15; ++i)               //单顺子
	{
		for(j = i; card[j] && j < 15; ++j)
		{
			card[j]--;
			if(j - i + 1 >= 5) dfs(discard + 1);    //如果多于5张向下搜索
		}
		for(; j > i;) card[--j]++;
	}
	for(int i = 3, j; i <= 15; ++i)             //双顺子
	{
		for(j = i; card[j] >= 2 && j < 15; ++j)
		{
			card[j] -= 2;
			if(j - i + 1 >= 3) dfs(discard + 1);
		}
		for(; j > i;) card[--j]+=2;
	}
	for(int i = 3, j; i <= 15; ++i)            //三顺子
	{
		for(j = i; card[j] >= 3 && j < 15; ++j)
		{
			card[j] -= 3;
			if(j - i + 1 >= 2) dfs(discard + 1);
		}
		for(; j > i;) card[--j] += 3;
	}              //我在思考是不是把顺子什么写个子程序会更简洁？
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
			if(!x) card[y - 1]++;       //Joker要分开存，因为它们并不能组成对牌
			else if(x == 1) card[14]++; //A -> 14
			else card[x]++;
		}
		dfs(0);
		printf("%d\n",ans);
	}
	return 0;
}
