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
	if(discard > ans) return; //�����Լ�֦
	int times = 0;
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i <= 14; i++) cnt[card[i]]++;

	while(cnt[4])
	{
		cnt[4]--;
		times++;                //ը��
		if(cnt[2] >= 2) cnt[2]-=2;         //�ܲ��ܴ���
		else if(cnt[1] >= 2)cnt[1]-=2;
	}
	for(; cnt[3];)
	{
		cnt[3]--;
		times++;                //������
		if(cnt[2]) cnt[2]--;             //�ܲ��ܴ�һ
		else if(cnt[1]) cnt[1]--;
	}                  //����˼��������һ���Ĵ���д���ӳ����ǲ��Ǹ���ࣿ
	if(card[0] && card[1] && cnt[1]>=2) times--;     //����ʣ�µĵ�����û����ը
	times += cnt[1] + cnt[2];
	ans = std::min(times + discard,ans);

	for(int i = 3, j; i < 15; ++i)               //��˳��
	{
		for(j = i; card[j] && j < 15; ++j)
		{
			card[j]--;
			if(j - i + 1 >= 5) dfs(discard + 1);    //�������5����������
		}
		for(; j > i;) card[--j]++;
	}
	for(int i = 3, j; i <= 15; ++i)             //˫˳��
	{
		for(j = i; card[j] >= 2 && j < 15; ++j)
		{
			card[j] -= 2;
			if(j - i + 1 >= 3) dfs(discard + 1);
		}
		for(; j > i;) card[--j]+=2;
	}
	for(int i = 3, j; i <= 15; ++i)            //��˳��
	{
		for(j = i; card[j] >= 3 && j < 15; ++j)
		{
			card[j] -= 3;
			if(j - i + 1 >= 2) dfs(discard + 1);
		}
		for(; j > i;) card[--j] += 3;
	}              //����˼���ǲ��ǰ�˳��ʲôд���ӳ�������ࣿ
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
			if(!x) card[y - 1]++;       //JokerҪ�ֿ��棬��Ϊ���ǲ�������ɶ���
			else if(x == 1) card[14]++; //A -> 14
			else card[x]++;
		}
		dfs(0);
		printf("%d\n",ans);
	}
	return 0;
}
