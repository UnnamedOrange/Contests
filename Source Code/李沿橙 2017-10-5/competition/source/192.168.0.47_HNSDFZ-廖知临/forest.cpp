#include<bits/stdc++.h>
using namespace std;
int n,use[1005];
inline int read()//¶ÁÈëÓÅ»¯
{
  	int num=0;
  	char c;
  	while(isspace(c=getchar()));
  	while(num=num*10+c-48,isdigit(c=getchar()));
  	return num;
}
struct a{
	int x;
	int y;
}num[1005];
int main()
{
    freopen("forset.in","r",stdout);
	freopen("forest.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++)	use[i]=read();
    for(int i=1;i<=n-1;i++)
	{
		int a=read(),b=read();
	}
    return 0;
}
