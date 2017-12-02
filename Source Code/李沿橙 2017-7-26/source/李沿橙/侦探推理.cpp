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
#include <bitset>
using std::cin;
using std::cout;
using std::endl;

std::string input;
int n, m, p;
std::map<std::string, int> mapSI;
std::map<int, std::string> mapIS;
std::map<std::string, int> mapDay;
const char guilty[] = "guilty";
struct analyzer
{
	const char* pStr;

	int GETCHAR()
	{
		if(!*pStr) return EOF;
		return *(pStr++);
	}

	analyzer(const char* pStr) : pStr(pStr)
	{
	}

	void operator>> (std::string& str)
	{
		str.clear();
		char ch = GETCHAR();
		while(!(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z'))
			ch = GETCHAR();
		while(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
		{
			str += ch;
			ch = GETCHAR();
		}
	}
};

struct edge
{
	int type;
	int to;
	int status;

	edge(int type = 0, int to = 0, int status = 0)
	{
	}
};
std::vector<std::vector<edge> > edges;

void dealP(analyzer& ain, int from, int to)
{
	std::string temp;
	ain >> temp;
	if(temp == "not")
	{
		ain >> temp;
		if(temp == guilty)
		{
			edges[from].push_back(edge(0, to, false));
		}
	}
	else if(temp == guilty)
	{
		edges[from].push_back(edge(0, to, true));
	}
}
void dealDay(analyzer& ain, int from)
{
	std::string temp;
	ain >> temp;
	if(temp != "is") return;
	ain >> temp;
	if(!mapDay.count(temp))	return;
	edges[from].push_back(edge(1, mapDay[temp]));
}

void deal()
{
	std::getline(cin, input);
	analyzer ain(input.c_str());

	int from = 0;
	int to = 0;
	int day = -1;
	std::string temp;
	ain >> temp;
	from = mapSI[temp];

	ain >> temp;
	if(temp == "I")
	{
		to = from;
		ain >> temp;
		if(temp != "am") return;
		dealP(ain, from, to);
	}
	else if(mapSI.count(temp))
	{
		to = mapSI[temp];
		ain >> temp;
		if(temp != "is") return;
		dealP(ain, from, to);
	}
	else if(temp == "Today")
	{
		dealDay(ain, from);
	}
}

void run()
{
	mapDay["Monday"] = 1;
	mapDay["Tuesday"] = 2;
	mapDay["Wednesday"] = 3;
	mapDay["Thursday"] = 4;
	mapDay["Friday"] = 5;
	mapDay["Saturday"] = 6;
	mapDay["Sunday"] = 7;

	std::getline(cin, input);
	sscanf(input.c_str(), "%d %d %d", &n, &m, &p);
	edges.resize(n + 1);
	for(int i = 1; i <= n; i++)
	{
		std::getline(cin, input);
		mapSI[input] = i;
		mapIS[i] = input;
	}

	for(int i = 1; i <= p; i++)
	{
		deal();
	}

	for(int i = 1; i <= p; i++)
	{
		
	}
}

int main()
{
	run();
	return 0;
}
