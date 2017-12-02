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

char word[105];
int times[26];

namespace Regular
{
	bool isPrime(int x)
	{
		if(x<=1) return false;
		int times=sqrt(x);
		for(int i=2; i<=times; i++)
		{
			if(x%times==0) return false;
		}
		return true;
	}

	void run()
	{
		int length=strlen(word);
		for(int i=0; i<length; i++)
		{
			times[word[i]-'a']++;
		}

		int maxi=0;
		int mini=0x7f; //127
		for(int i=0; i<26; i++)
		{
			if(times[i]>maxi) maxi=times[i];
			if(times[i]<mini && times[i]) mini=times[i];
		}

		if(isPrime(maxi-mini))
		{
			printf("Lucky Word\n%d\n",maxi-mini);
		}
		else
		{
			printf("No Answer\n0\n");
		}
	}
	void input()
	{
		scanf("%s",word);
	}
}

int main()
{
	Regular::input();
	Regular::run();
	return 0;
}
