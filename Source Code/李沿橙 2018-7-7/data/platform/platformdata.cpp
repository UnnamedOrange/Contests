#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define P puts("lala")
#define ln putchar('\n')
#define fi first
#define se second
using namespace std;
inline int read()
{
	char ch=getchar();int g=1,re=0;
	while (ch<'0'||ch>'9') {if(ch=='-')g=-1;ch=getchar();}
	while(ch<='9'&&ch>='0') re=(re<<1)+(re<<3)+ch-48,ch=getchar();
	return re*g;
}
typedef pair<int,int> pii;
typedef long long ll;
typedef double db;
typedef unsigned long long ul;

int Rand(int l,int r)
{
	if(l>r) return 0;
	return rand()%(r-l+1)+l;
}
int neg()
{
	return ((rand()&1)==1?1:-1);
}

const int inf=0x7fffffff;
const int N=1000050;

char s[N];
void wj()
{
	freopen("platform.in","w",stdout);
}
int main()
{
	wj();
	srand((unsigned long long)new char);
	int k=5,n=1e9,m=1e9,T,Q,opt,typ,mm=100,r;
	n=Rand(48000,50000);
	m=Rand(5000,15000);
	for(int i=1;i<=n;++i) s[i]='a'+Rand(0,3);
	printf("%s\n",s+1);
	for(int i=1;i<=n;++i) printf("%d ",11);
	/*for(int i=1;i<=n-m;++i) 
	{
		s[i]='a'+Rand(0,3);
		if(rand()%1000==0) s[i]=Rand('y','z');
	}
	for(int i=n-m+1;i<=n;++i) s[i]='z';*/
	//printf("%s\n",s+1);
	//for(int i=1;i<=n-m;++i) printf("%d ",Rand(0,mm));
	//for(int i=n-m+1;i<=n;++i) printf("%d ",Rand(0,5));
	/*for(int i=1;i<=n;++i) 
		if(i%30000==0) putchar('a'+Rand(1,5));
		else putchar('a');*/
	/*for(int j=1;j<=2;++j) for(int i=(j-1)*90000+1;i<=j*90000;++i)
		if(i%22000) putchar('a'+j);
		else putchar('a');
	for(int i=180001;i<=n;++i) putchar('a'+Rand(0,1));
	ln;
	for(int i=1;i<=n;++i) printf("%d ",Rand(0,mm));*/
	return 0;
}
