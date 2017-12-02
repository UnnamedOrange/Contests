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

int m,n;
int ans;

namespace Regular
{
	struct translate: public std::queue<int>
	{
		std::vector<bool> status;

		translate():status(1005)
		{}

		bool readIn(int word)
		{
			if(status[word])
			{
				return false;
			}
			if(std::queue<int>::size()>=m)
			{
				int popElement=std::queue<int>::front();
				status[popElement]=false;
				std::queue<int>::pop();
			}
			std::queue<int>::push(word);
			status[word]=true;
			return true;
		}
	};

	void run()
	{
		translate solution;
		for(int i=0; i<n; i++)
		{
			int word;
			scanf("%d",&word);
			ans+=solution.readIn(word);
		}
		printf("%d\n",ans);
	}
}

namespace Init
{
	void input()
	{
		scanf("%d%d",&m,&n);
	}
}

int main()
{
	Init::input();
	Regular::run();
	return 0;
}
