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

int Rand(int l,int r)
{
#ifdef __linux__
	return rand()%(r-l+1)+l;
#endif
	return (rand()<<15|rand())%(r-l+1)+l;
}
int neg()
{
	return rand()%2==1?-1:1;
}

const int N=55;
int val[N][N];
pii p[N*N];

void wj()
{
#ifndef ONLINE_JUDGE
    freopen("lethe.in","w",stdout);
#endif
}
int main()
{
	srand((unsigned long long)new char);
	wj();
	int n,m,k;
	//n=10; m=15; k=6;
	n=50-Rand(1,5); m=n*n/6-Rand(1,50); k=Rand(1,100);
	cout<<n<<' '<<m<<' '<<k<<endl;
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j)
	{
		if(i+j&1) val[i][j]=Rand(1,1000000);
		else val[i][j]=0;
	}
	for(int i=1;i<=k;++i) 
	{
		p[i].fi=Rand(1,n); p[i].se=Rand(1,n);
		val[p[i].fi][p[i].se]=0;
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) printf("%d%c",val[i][j],j==n?'\n':' ');
	for(int i=1;i<=k;++i) printf("%d %d\n",p[i].fi,p[i].se);
    return 0;
}
