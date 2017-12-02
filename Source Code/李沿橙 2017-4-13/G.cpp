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

const int maxn=105;
int n;
std::vector<std::string> str;
std::set<std::string> Set;
bool vis[maxn];
int indexes[maxn];
int count_;
bool sign=0;

bool calc()
{
	std::string temp;
	temp.clear();
	for(int i=0; i<count_; i++)
	{
		temp+=str[indexes[i]];
	}
	//cout<<temp<<std::endl<<std::endl;
	if(Set.count(temp))
	{
		cout<<temp;
		return true;
	}
	Set.insert(temp);
	return false;
}

void search(int index)
{
	for(int i=0; i<n; i++)
	{
		if(!vis[i])
		{
			vis[i]=true;
			indexes[count_++]=i;
			if(index>1)
			{
				search(index-1);
				if(sign) return;
			}
			else
			{
				if(calc())
				{
					sign=true;
					return;
				}
			}
			count_--;
			vis[i]=false;
		}
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=0; i<n; i++)
	{
		std::string temp;
		cin>>temp;
		str.push_back(temp);
	}
	std::sort(str.begin(),str.end());

	for(int i=2; i<=n-1; i++)
	{
		search(i);
	}
	return 0;
}
