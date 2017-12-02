#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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

int N;
std::vector<int> Numbers;

void input()
{
	scanf("%d",&N);
	for(int i=0; i<N; i++)
	{
		int input;
		scanf("%d",&input);
		Numbers.push_back(input);
	}
	std::sort(Numbers.begin(),Numbers.end()); //������
}

void run()
{
	int ans=0;
	for(int i=2; i<Numbers.size(); i++) //ǰ��������������
	{
		bool sign=false;
		for(int j=0; j<i; j++)
		{
			for(int k=j+1; k<i; k++)
			{
				if(Numbers[j]+Numbers[k]==Numbers[i])
				{
					sign=true;
					break;
				}
			}
			if(sign) break;
		}
		if(sign) ans++;
	}

	printf("%d",ans);
}

int main()
{
#ifndef DEBUG
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif
	input();
	run();
	return 0;
}
