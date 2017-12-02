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
ll ans,cnt,sum;
int n,m;
int a[110][110];
int f[110],s[110];
bool del[110],de[110];
int main()
{
	freopen("steal.in","r",stdin);
	freopen("steal.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	a[i][j]=read(),sum+=a[i][j],f[j]=max(f[j],a[i][j]),s[i]=max(s[i],a[i][j]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		if(a[i][j]==0)ans--;
		ll h=a[i][j];
		int n1=0,m1=0;
		for(int k=1;k<=max(n,m);k++)
	 	{
	 		if(h==s[k]&&!de[k])n1++,de[k]=1;
	 		if(h==f[k]&&!del[k])m1++,del[k]=1;
	 	}
	 	cnt+=max(n1,m1);
	 	ans+=(ll)h*max(n1,m1);
	}
	ans=sum-ans;
	ans-=(n*m-cnt);
	printf("%lld\n",ans);
}