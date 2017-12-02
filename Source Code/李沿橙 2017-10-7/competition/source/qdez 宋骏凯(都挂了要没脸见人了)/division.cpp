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
map<ll,int> mp;
int go[200000],a[200000],f[200000];
ll s[200000];
const double eps=1e-7;
bool ok(int x)
{	double p=sqrt(1.0*x+0.5);
	if(int(p)*int(p)==x) return true;
	return false;
}
int main()
{   freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	int n,k; scanf("%d%d",&n,&k);
	memset(f,0x7f,sizeof(f));
	if(k==1)
	{	if((ll)n*k<=100000000) printf("1\n\n");
		else
		{
		for(rint i=1;i<=n;i++) scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
		f[1]=(ok(a[1])?-1:1); f[0]=0;
		for(rint i=2;i<=n;i++)
		for(rint j=0;j<i;j++)
		if(!ok(s[i]-s[j-1])&&f[j]!=-1) if(f[j]+1<f[i])f[i]=min(f[i],f[j]+1),go[i]=j;
		int minn=1000000000,kk=-1;
		for(rint i=0;i<=n;i++)
		if(!ok(s[n]-s[i])&&f[i]<minn) minn=f[i],kk=i;
		printf("%d\n",minn+1);
		while(go[kk])
		{	printf("%d ",kk);
			kk=go[kk];
		}
		if(kk) printf("%d\n",kk);
		}
	}
	else printf("1\n\n");
 	return 0;
}



