#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<cmath>
#include<ctime>
#include<queue>
#include<map>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
int f[10000];
int main()
{   freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	int n; cin>>n; f[1]=1;
	for(rint i=2;i<=n;i++)
	{	f[i]=f[i-1];
		for(rint j=1;j<i;j++) f[i]=(f[i]+f[i-j])%7;
	}
	cout<<f[n]<<endl;
 	return 0;
}


