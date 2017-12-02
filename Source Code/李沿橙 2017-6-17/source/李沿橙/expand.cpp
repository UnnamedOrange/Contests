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
inline int readIn()
{
	int a=0;
	scanf("%d",&a);
	return a;
}

class Expand
{
	enum
	{
	    Lower=1,
	    Upper,
	    Star
	};
	int expandStyle;

	int repeatTime;

	enum
	{
	    Normal=1,
	    Reverse
	};
	int order;

	std::string origin;

	inline bool isDigit(char ch)
	{
		return ch>='0' && ch<='9';
	}
	inline bool isAlpha(char ch)
	{
		return ch>='a' && ch<='z';
	}

	bool isExpand(char from, char to)
	{
		if(isDigit(from) && isDigit(to) && from<to) return true;
		if(isAlpha(from) && isAlpha(to) && from<to) return true;
		return false;
	}

	char make(char ch)
	{
		if(expandStyle==Upper && isAlpha(ch)) return ch-'a'+'A'; //小心溢出
		else if(expandStyle==Star) return '*';
		return ch;
	}
	void expandOne(std::string &str, char from, char to)
	{
		if(order==Normal)
		{
			for(char i=from+1; i<=to-1; i++)
			{
				char output=make(i);
				for(int j=1; j<=repeatTime; j++)
				{
					str.push_back(output);
				}
			}
		}
		else if(order==Reverse)
		{
			for(char i=to-1; i>=from+1; i--)
			{
				char output=make(i);
				for(int j=1; j<=repeatTime; j++)
				{
					str.push_back(output);
				}
			}
		}
	}

public:
	Expand(int p1, int p2, int p3, const char *lpStr):expandStyle(p1),repeatTime(p2),order(p3),origin(lpStr)
	{
	}

	void expandAndOutput()
	{
		std::string ans;
		for(int i=0; i<origin.length(); i++)
		{
			if(i && i<origin.length()-1 && //至少减号两边要有字符
			        origin[i]=='-' && isExpand(origin[i-1],origin[i+1])) //当前字符为减号且两边字符符合条件才展开
			{
				expandOne(ans, origin[i-1],origin[i+1]);
			}
			else
			{
				ans.push_back(origin[i]);
			}
		}
		printf("%s\n",ans.c_str());
	}
};

int p1,p2,p3;
char str[200];

namespace Regular
{
	void run()
	{
		Expand(p1,p2,p3,str).expandAndOutput();
	}
	void input()
	{
		p1=readIn();
		p2=readIn();
		p3=readIn();
		scanf("%s",str);
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
