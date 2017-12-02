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
using namespace std;
inline int readIn()
{
	int a;
	scanf("%d",&a);
	return a;
}

const int maxn=200005;
int n,m;
long long s;
struct mine
{
	int weight;
	int value;

	void input()
	{
		weight = readIn();
		value = readIn();
	}
} mines[maxn];
struct area
{
	int l;
	int r;

	void input()
	{
		l = readIn();
		r = readIn();
	}
} areas[maxn];
long long sum[maxn];
long long count_[maxn];

long long check(int w)
{
	long long res=0;
	for(int i=1; i<=n; i++)
	{
		sum[i]=sum[i-1];
		count_[i]=count_[i-1];
		if(mines[i].weight>=w)
		{
			sum[i]+=mines[i].value;
			count_[i]++;
		}
	}
	for(int i=1; i<=m; i++)
	{
		int l=areas[i].l;
		int r=areas[i].r;
		res+=(long long)(count_[r] - count_[l-1]) * (sum[r] - sum[l-1]);
	}
	return res-s;
}
//long long abs(long long a)
//{
//	if(a<0) return -a;
//	return a;
//}
void run()
{
	n=readIn();
	m=readIn();
	cin>>s;
	int maxW=0;
	for(int i=1; i<=n; i++)
	{
		mines[i].input();
		maxW=std::max(maxW, mines[i].weight);
	}
	for(int i=1; i<=m; i++)
	{
		areas[i].input();
	}

	int left = 0, right = maxW;
	long long ans = 0;
	long long leftVal = check(left), rightVal = check(right);
	while(right - left > 1)
	{
		int mid = (left + right) >> 1;
		ans = check(mid);
		if(ans == 0)
		{
			break;
		}
		if(ans > 0) //比S大
		{
			left = mid; //W尽量高使S减小
			leftVal = ans;
		}
		else
		{
			right = mid; //W尽量低使S增大
			rightVal = ans;
		}
	}
	if(ans)
	{
		ans = std::min(abs(leftVal), abs(rightVal));
//		if(leftVal<rightVal) ans=leftVal;
//		else ans = rightVal;
	}
	cout<<ans<<endl;
}

int main()
{
	run();
	return 0;
}
