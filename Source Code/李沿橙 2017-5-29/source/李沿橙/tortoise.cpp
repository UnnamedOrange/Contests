#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

int n,m;
int board[355];
int card[125];

namespace Violent
{
	int ans;
	bool status[125];
	std::vector<int> sequeue;
	void dfs()
	{
		if(sequeue.size()==m)
		{
			int pos=1;
			int temp=board[pos];
			for(int i=0; i<sequeue.size(); i++)
			{
				pos+=card[sequeue[i]];
				temp+=board[pos];
			}
			ans=std::max(ans,temp);
			return;
		}
		for(int i=1; i<=m; i++)
		{
			if(status[i]) continue;
			status[i]=true;
			sequeue.push_back(i);
			dfs();
			status[i]=false;
			sequeue.pop_back();
		}
	}

	void run()
	{
		dfs();
		printf("%d\n",ans);
	}
}

namespace Regular
{
	int status[55][55][55][55];
	void run()
	{
		int num[5]= {0};
		for(int i=1; i<=m; i++)
		{
			num[card[i]]++;
		}
		status[0][0][0][0]=board[0];

#define GO(x) for(int c##x=0; c##x<=num[x]; c##x++)
#define INDEX(c1,c2,c3,c4) ((c4)*4+(c3)*3+(c2)*2+(c1)+1)
#define ORIGIN status[c1][c2][c3][c4]
		GO(1) GO(2) GO(3) GO(4)
		{
			if(c1) ORIGIN=std::max(ORIGIN,status[c1-1][c2][c3][c4]);
			if(c2) ORIGIN=std::max(ORIGIN,status[c1][c2-1][c3][c4]);
			if(c3) ORIGIN=std::max(ORIGIN,status[c1][c2][c3-1][c4]);
			if(c4) ORIGIN=std::max(ORIGIN,status[c1][c2][c3][c4-1]);
			ORIGIN+=board[INDEX(c1,c2,c3,c4)];
		}
		printf("%d\n",status[num[1]][num[2]][num[3]][num[4]]);
	}
}

namespace Init
{
	void input()
	{
		scanf("%d%d",&n,&m);
		for(int i=1; i<=n; i++)
		{
			scanf("%d",&board[i]);
		}
		for(int i=1; i<=m; i++)
		{
			scanf("%d",&card[i]);
		}
	}
}

int main()
{
	Init::input();
	if(m<=8)
		Violent::run();
	else
		Regular::run();
	return 0;
}
