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
typedef long long ll;
ll A,B;

void gcdex(ll a, ll b, ll& gcd, ll& x, ll& y)
{
	if(!b)
	{
		x=1;
		y=0;
		gcd=a;
		return;
	}
	gcdex(b, a%b, gcd, y, x);
	y-=x*(a/b);
}

void run()
{
	A=readIn();
	B=readIn();
	ll gcd,x,y;
	gcdex(A, B, gcd, x, y);
	//Ax+By=1
	//(保证有解，gcd=1)
	ll deltaX = B; // /gcd gcd=1
	x%=deltaX;
	if(x<=0)
		x+=deltaX;
	cout<<x<<endl;
}

int main()
{
	run();
	return 0;
}
