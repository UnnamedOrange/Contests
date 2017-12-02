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

int c;
int n;
const char *name[]=
{
	"xiaoyong",
	"xiaoshi"
};

namespace Regular
{
	int f[105];
	int dp(int x)
	{
		if(f[x]!=-1) return f[x];
		if(x==1) return f[x] = true;
		if(x==2) return f[x] = false;
		return f[x]=!dp(x-1);
//		if(x==3) return f[x] = true;
//		if(x==4) return f[x] = false;
	}

	//设全部都竖着下，那么胜者与n的奇偶有关
	//如果先手知道自己竖着下会输，那么他会试着
	//横着下，但是对手也知道如果不把横着下的
	//那一块对齐他就会输。所以对手始终保持对齐
	//所以不影响胜负

	//假设后手想不对齐地横着下以扭转局势，前提
	//是先手首先横着下了。既然横着下有可能会输
	//所以先手不会横着下。

	//故得证：胜者只与n的奇偶有关
	void run()
	{
		memset(f,-1,sizeof(f));
		while(c--)
		{
			scanf("%d",&n);
			printf("%s\n",name[n%2]);
		}
	}
	void input()
	{
		scanf("%d",&c);
	}
}

int main()
{
#ifndef DEBUG
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	Regular::input();
	Regular::run();
	return 0;
}
