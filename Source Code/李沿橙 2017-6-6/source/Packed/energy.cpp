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

const int maxn=105;
int n;
int num[maxn];
int f[2*maxn][2*maxn]; //要复制为2n份

struct ball
{
	int left;
	int right;

	ball(int left=0,int right=0):left(left),right(right)
	{
	}
} balls[2*maxn];

namespace Regular
{
	int dp(int from=1, int to=n, int depth=1)
	{
		if(f[from][to]!=-1) return f[from][to];
		if(from==to) return f[from][to]=0;
		if(to-from==1) //边界情况
		{
			return f[from][to]=balls[from].left * balls[to].right * balls[from].right;
		}

		int ans=0;
		for(int i=from; i<to; i++)
		{
			ans=std::max(ans,dp(from,i,depth+1)+dp(i+1,to,depth+1)+
			             balls[from].left * balls[to].right * balls[i].right); //一般的划分DP写法
		}
		return f[from][to]=ans;
	}

	void run()
	{
		memset(f,-1,sizeof(f));
		int ans=0;
		for(int i=1; i<=n; i++)
		{
			ans=std::max(ans,dp(i,i+n-1)); //这里相当于在枚举其中的一个分割点，然后将剩余问题通用化
		}
		printf("%d\n",ans);
	}
	void input()
	{
		scanf("%d",&n);

		for(int i=1; i<=n; i++)
		{
			scanf("%d",&num[i]);
		}

		for(int i=1; i<=n; i++) //将给的数字转换为珠子，方便思考
		{
			balls[i].left=num[i];
			if(i!=n) balls[i].right=num[i+1];
			else balls[i].right=num[1];
		}
		for(int i=1,j=n+1; i<=n; i++,j++) //复制
		{
			balls[j]=balls[i];
		}
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
