/*
	设程序返回值为x，
	若x==0，则为AC
	若1<=x<=99，则为WA
	若100<=x<=200，则该测试点得分(x-100)%
*/
#include "testlib.h"
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define forE(i,x) for(int i=head[x];i!=-1;i=ne[i])
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int,int> pin;
#define mk(a,b) make_pair(a,b)
#define lowbit(x) ((x)&(-(x)))
#define sqr(a) ((a)*(a))
#define clr(a) (memset((a),0,sizeof(a)))
#define ls ((x)<<1)
#define rs (((x)<<1)|1)
#define mid (((l)+(r))>>1)
#define pb push_back
#define w1 first
#define w2 second

bool isLemon = false;



const double eps = 1e-6;
int n,m,q;
const int maxn=1005;
int num,res[maxn],head[maxn],t[maxn<<1],ne[maxn<<1];
inline void addedge(int x,int y){
	ne[++num]=head[x];head[x]=num;t[num]=y;
	ne[++num]=head[y];head[y]=num;t[num]=x;
}
int S[maxn],top;
inline bool dfs_edge(int x,int f,int ed){
	S[++top]=x;
	if(x==ed){
		return 1;
	}
	forE(i,x)if(t[i]!=f){
		if(dfs_edge(t[i],x,ed))return 1;
	}top--;
	return 0;
}
void judge() {
	
	
	n = inf.readInt();
	inf.readSpace();
	m = inf.readInt();
	inf.readSpace();
	q = inf.readInt();
	inf.readEoln();
	rep(i,1,n)head[i]=-1;
	rep(i,1,n-1){
		int x,y;
		x = inf.readInt();
		inf.readSpace();
		y = inf.readInt();
		inf.readEoln();
		addedge(x,y);
	}
	rep(i,1,m){
		res[i]=ouf.readInt();
		if(i!=m)ouf.readSpace();
	}
	char st[105];
	rep(i,1,q){
		int a,b,c;
		a=inf.readInt();
		inf.readSpace();
		b=inf.readInt();
		inf.readSpace();
		c=inf.readInt();
		inf.readEoln();
		top=0;
		dfs_edge(res[a],-1,res[b]);
		bool flag=0;
		rep(i,1,top)if(c==S[i])flag=1;
		if(!flag)
			quitf(_wa,"Wrong Answer");	}
	// double x, y;
	// char st[100];
	// while (fscanf(ans, "%lf", &x) != EOF) {
	    // sprintf(st, "wrong answer expect %.10lf but found EOF", x);
		// if (fscanf(out, "%lf", &y) != 1) result(0, st);
		// sprintf(st, "wrong answer expect %.10lf but found %.10lf", x, y);
		// if (isnan(y) || fabs(x - y) > eps) result(0, st);
	// }

	// char s[10];
	// if (fscanf(out, "%s", s) != EOF) result(0, "wrong answer expect EOF but found some character");
	quitf(_ok,"Right Output");
}

// 可以输出信息到argv[4]的文件里


int main(int argc, char **argv)
{
	registerTestlibCmd(argc, argv);

	judge();
	

	return 0;
}
