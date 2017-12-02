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
	if(discard > ans) return; //�����Լ�֦
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i <= 14; i++) cnt[card[i]]++; //ʹ�����ַ�ʽ���㲻��˳�ӵ��������ö�
	int noStraight = 0;

	while(cnt[4]) //��ը��
	{
		cnt[4]--;
		noStraight++;
		if(cnt[2] >= 2) cnt[2]-=2; //�Ĵ�����
		else if(cnt[1] >= 2) cnt[1]-=2; //�Ĵ�����
	}
	while(cnt[3]) //������
	{
		cnt[3]--;
		noStraight++;
		if(cnt[2]) cnt[2]--; //������
		else if(cnt[1]) cnt[1]--; //����һ
	}
	if(card[0] && card[1] && cnt[1] >= 2) noStraight--; //Joker�Ƿֿ���ģ����ǿ��Ե�����һ�Գ�ȥ��������У��һ��
	noStraight += cnt[1] + cnt[2]; //����û��Ķ��Ӻ͵�����
	ans = std::min(noStraight + discard,ans); //�������Ž�

	for(int i = 3; i <= 14; i++) //��3��A����˳��
	{
		int j = i;
		for(; card[j] && j <= 14; j++)
		{
			card[j]--;
			if(j - i + 1 >= 5) dfs(discard + 1); //�������5����������
		}
		while(j > i) card[--j]++; //��˷
	}
	for(int i = 3; i <= 14; i++) //˫˳��
	{
		int j = i;
		for(; card[j] >= 2 && j <= 14; j++)
		{
			card[j] -= 2;
			if(j - i + 1 >= 3) dfs(discard + 1);
		}
		while(j > i) card[--j] += 2;
	}
	for(int i = 3; i <= 14; i++) //��˳��
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
			if(!x) card[y - 1]++; //Joker�ֱ����0��1����Ϊ��˳���в��ܴ�Joker
			else if(x == 1) card[14]++; //A����14��λ�ã���Ϊ˳�ӵ�˳����JQKA���պ�����
			else card[x]++; //������������
		}
		dfs();
		printf("%d\n",ans);
	}
	return 0;
}
