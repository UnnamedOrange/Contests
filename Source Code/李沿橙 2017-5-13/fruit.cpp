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
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

int n;
int score;
std::priority_queue<int, std::vector<int>, std::greater<int> > heap;

void run_Regular()
{
	for(int i=1; i<n; i++)
	{
		int reg1=heap.top();
		heap.pop();
		int reg2=heap.top();
		heap.pop();
		score+=reg1+reg2;
		heap.push(reg1+reg2);
	}
	printf("%d",score);
}

void input()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		int input;
		scanf("%d",&input);
		heap.push(input);
	}
}

int main()
{
#ifndef DEBUG
	freopen("fruit.in","r",stdin);
	freopen("fruit.out","w",stdout);
#endif
	input();
	run_Regular();
	return 0;
}
