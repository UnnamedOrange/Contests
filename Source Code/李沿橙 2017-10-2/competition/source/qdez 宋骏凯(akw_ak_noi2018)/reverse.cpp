#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<ctime>
#include<map>
#include<queue>
#include<vector>
#define rint register int
#define debug(x) cerr<<#x<<"="<<x<<endl
#define fgx cerr<<"-------------"<<endl
typedef long long ll;
using namespace std;
char c[1000000];
int pre[100010],s[100010];
int main()
{	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%s",c+1);
	int n=strlen(c+1),ans=1000000000;
	for(rint i=1;i<=n;i++) pre[i]=pre[i-1]+(c[i]=='1');
	for(rint i=n;i>=1;i--) s[i]=s[i+1]+(c[i]=='0');
	for(rint i=1;i<=n+1;i++)
	ans=min(ans,pre[i-1]+s[i]);
	cout<<ans<<endl;
	return 0;
}

