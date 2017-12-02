#pragma GCC optimize(2)
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<set>
#include<bitset>
#include<map>

#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)

using namespace std;

typedef long long LL;
typedef double db;

int get(){
	char ch;
	while(ch=getchar(),(ch<'0'||ch>'9')&&ch!='-');
	if (ch=='-'){
		int s=0;
		while(ch=getchar(),ch>='0'&&ch<='9')s=s*10+ch-'0';
		return -s;
	}
	int s=ch-'0';
	while(ch=getchar(),ch>='0'&&ch<='9')s=s*10+ch-'0';
	return s;
}

const int N = 150003;

int n,k;
int a[N],b[N];
LL now;

int s[2][N];
int t[2];

void insert(int c,int v){
	int x=++t[c];
	s[c][x]=v;
	for(;x>1&&s[c][x]<s[c][x>>1];x>>=1)swap(s[c][x],s[c][x>>1]);
}

void pop(int c){
	int x=1;
	s[c][1]=s[c][t[c]--];
	for(;x*2<=t[c];){
		int y=x*2;
		if (y<t[c]&&s[c][y+1]<s[c][y])y++;
		if (s[c][y]>=s[c][x])break;
		swap(s[c][y],s[c][x]);
		x=y;
	}
}

int check(int v){
	now=t[0]=t[1]=0;
	int cnt=0;
	fo(i,1,n){
		LL v1=2e+9,v2=2e+9;
		insert(0,a[i]);
		if (t[1])v2=s[1][1];
		v1=s[0][1];
		if (v1<v2&&b[i]-v+v1<0){
			cnt++;
			pop(0);
			insert(1,v-b[i]);
			now=now+b[i]-v+v1;
		}
		else
			if (b[i]-v+v2<0){
				pop(1);
				insert(1,v-b[i]);
				now=now+b[i]-v+v2;
			}
	}
	return cnt;
}

int main(){
	freopen("orz.in","r",stdin);
	freopen("orz.out","w",stdout);
	n=get();k=get();
	fo(i,1,n)a[i]=get();
	fo(i,1,n)b[i]=get();
	int l=0,r=1e+9;
	LL ans=0;
	while(l<=r){
		int mid=(l+r)/2;
		if (check(mid)>k)r=mid-1;
		else{
			l=mid+1;
			ans=now+1ll*k*mid;
		}
	}
	printf("%lld\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
