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

std::map<std::string, int> MapSI;
std::map<int, std::string> MapIS;
int mapCount;
int n;
std::vector<int> src;
std::vector<int> des;

namespace Regular
{
	void run()
	{
		int start=0;
		for(int i=1; i<=n; i++) //n已预处理，为地点数
		{
			if(!src[i])
			{
				start=i;
				break;
			}
		}

		while(des[start])
		{
			printf("%s %s\n",MapIS[start].c_str(),MapIS[des[start]].c_str());
			start=des[start];
		}
	}
}

int RegisterKey(char *name)
{
	if(!MapSI.count(name))
	{
		mapCount++;
		MapSI[name]=mapCount;
		MapIS[mapCount]=name;
		return mapCount;
	}
	else return MapSI[name];
}

void input()
{
	scanf("%d",&n);
	src.resize(n+2); //有n+1个
	des.resize(n+2);
	for(int i=1; i<=n; i++)
	{
		char buffer[2][20];
		scanf("%s %s",buffer[0],buffer[1]);
		int from = RegisterKey(buffer[0]);
		int to = RegisterKey(buffer[1]);
		src[to]=from;
		des[from]=to;
	}
	n++; //预处理n
}

int main()
{
	input();
	Regular::run();
	return 0;
}
