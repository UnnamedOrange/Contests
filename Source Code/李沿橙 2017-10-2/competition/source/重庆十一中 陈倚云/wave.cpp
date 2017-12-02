#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
using namespace std;
inline int read()
{
	int X=0,w=1;
	char ch=0;
	while(ch<'0' || ch>'9')
	{
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
	return X*w;
}
int n,k;
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	n=read();
	k=read();
	int l=1,ma,mi,a;
	a=read();
	ma=a;
	mi=a;
	for(int i=2; i<=n; i++)
	{
		a=read();
		if((l+2)%2==1)
		{
			if(a>=mi+k)
			{
				l++;
				ma=a;
			}
			if(a<mi) mi=a;
		}
		else
		{
			if(a<=ma-k)
			{
				l++;
				mi=a;
			}
			if(a>ma) ma=a;
		}
	}
	printf("%d",l);
	return 0;
}
