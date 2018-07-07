#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#define P puts("lala")
#define cp cerr<<"lala"<<endl
#define fi first
#define se second
#define ln putchar('\n')
#define pb push_back
using namespace std;
inline int read()
{
    char ch=getchar();int g=1,re=0;
    while(ch<'0'||ch>'9'){if(ch=='-')g=-1; ch=getchar();}
    while(ch<='9'&&ch>='0') re=(re<<1)+(re<<3)+(ch^48),ch=getchar();
    return re*g;
}
typedef long long ll;
typedef pair<int,int> pii;

const int N=400050;
const int inf=0x3f3f3f3f;
char s[N];
int val[N],n,hei[N],sa[N],Rank[N],cnt[N],tt2[N];
void buildsa()
{
	int m=0,*x=Rank,*y=tt2;
	for(int i=1;i<=n;++i) cnt[x[i]=s[i]]++,m=max(m,x[i]);
	for(int i=2;i<=m;++i) cnt[i]+=cnt[i-1];
	for(int i=n;i;--i) sa[cnt[x[i]]--]=i;
	for(int k=1;k<n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;++i) y[++p]=i;
		for(int i=1;i<=n;++i) if(sa[i]>k) y[++p]=sa[i]-k;
		for(int i=1;i<=m;++i) cnt[i]=0;
		for(int i=1;i<=n;++i) cnt[x[y[i]]]++;
		for(int i=2;i<=m;++i) cnt[i]+=cnt[i-1];
		for(int i=n;i;--i) sa[cnt[x[y[i]]]--]=y[i];
		swap(x,y);
		p=1; x[sa[1]]=1;
		for(int i=2;i<=n;++i) x[sa[i]]=y[sa[i-1]]==y[sa[i]]
		&&y[sa[i-1]+k>n?0:sa[i-1]+k]==y[sa[i]+k>n?0:sa[i]+k]?p:++p;
		m=p;
		if(m>=n) break;
	}
	for(int i=1;i<=n;++i) Rank[sa[i]]=i;
}
void buildheight()
{
	int k=0;
	for(int i=1;i<=n;++i)
	{
		if(k>0) k--;
		int j=sa[Rank[i]-1];
		while(s[i+k]==s[j+k]) k++;
		hei[Rank[i]]=k;
	}
}

pii ans[N]; int tot=0;
ll lcp[N];

void wj()
{
#ifndef ONLINE_JUDGE
    freopen("platform.in","r",stdin);
    freopen("platform.out","w",stdout);
#endif
}
int main()
{
	wj();
	scanf("%s",s+1); n=strlen(s+1);
	memset(val,inf,sizeof(val));
	val[0]=0;
	for(int i=1;i<=n;++i) val[i]=read()+val[i-1];
	buildsa(); buildheight();

	ll rnk=0;
	for(int i=1;i<=n;++i) rnk+=n-sa[i]+1-hei[i];

	int siz=0;
	for(int i=1;i<=n;++i)
	{
		int l=hei[i],r=n-sa[i];
		while(l<r)
		{
			int mid=l+r>>1;
			if(val[sa[i]+mid]-val[sa[i]-1]<rnk-(mid-hei[i])) l=mid+1;
			else r=mid;
		}
		if(val[sa[i]+l]-val[sa[i]-1]==rnk-(l-hei[i])) ans[++tot]=pii(sa[i],sa[i]+l);
		l=1,r=siz;
		while(l<r)
		{
			int mid=l+r>>1;
			if(val[sa[i]+mid-1]-val[sa[i]-1]<lcp[mid]) l=mid+1;
			else r=mid;
		}
		if(l<=siz&&val[sa[i]+l-1]-val[sa[i]-1]==lcp[l]) ans[++tot]=pii(sa[i],sa[i]+l-1);

		if(siz<hei[i+1]) 
		{
			for(int j=siz+1;j<=hei[i+1];++j) lcp[j]=rnk-(j-siz)+1;
		}
		else if(siz>hei[i+1])
		{
			for(int j=hei[i+1]+1;j<=siz;++j) lcp[j]=0;
		}
		siz=hei[i+1];
		rnk-=n-sa[i]+1-hei[i];
	}
	sort(ans+1,ans+1+tot);
	printf("%d\n",tot);
	for(int i=1;i<=tot;++i) printf("%d %d\n",ans[i].fi,ans[i].se);
	//cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}
