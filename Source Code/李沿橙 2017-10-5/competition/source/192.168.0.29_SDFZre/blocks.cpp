#include<algorithm>
#include<iostream>
#include<cstdio>
#define Max(a,b) a=a>b?a:b
const int N=1000005;

int p[N],a[N]={0};
using namespace std;
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int k,n,m,ans,maxn;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&p[i])/*,maxn=max(maxn,p[i])*/;
	for(int i=1;i<=m;i++)
	{
		ans=0;
		scanf("%d",&k);
		for(int o=1;o<=n;o++) a[o]=(a[o-1]+p[o]);
		for(int o=1;o<=n;o++)
			for(int j=o+1;j<=n;j++)
				if(a[j]-a[o-1]>=k*(j-o+1))
				{
					ans=Max(ans,j-o+1);
				}
		cout<<ans<<" ";
	}
	//for(int i=1;i<=n;i++) cout<<a[i]<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
