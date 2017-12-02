#include <cmath>
#include <queue>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100010
#define ll long long
using namespace std;
inline int read() 
{ 
    int x=0,f=1;char ch=getchar(); 
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();} 
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} 
    return x*f; 
}
int main()
{
	srand(time(0));
	freopen("split10.in","w",stdout);
	ll T=10;
	cout<<T<<endl;
	for(int i=1;i<=T;i++)
	{
		ll n=(rand()^rand()<<15)*(rand()^rand()<<15)%10000000000000000ll+1;
		cout<<n<<endl;
	}
}