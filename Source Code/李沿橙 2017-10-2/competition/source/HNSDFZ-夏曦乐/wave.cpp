#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("wave.in","r",stdin);
    freopen("wave.out","w",stdout);
  }
}
inline void fileclose(){
  if(FileIO){
    fclose(stdin);
    fclose(stdout);
  }
}
/*
Time Limit  : 1sec
Memory Limit: 256MB
O2          : No
*/
int n,k,best;
ll m[2000001];
int dp1[2000001],dp2[2000001];

inline void update(int &a,int b){
  if(a<b)
    a=b;
  if(best<a)
    best=a;
}

void work1(){
  for(int i=1;i<n;++i)
    for(int j=i+1;j<=n;++j){
      if(m[j]>=m[i]+k)
	update(dp2[j],dp1[i]+1);
      if(m[j]<=m[i]-k&&dp2[i]!=0)
	update(dp1[j],dp2[i]+1);
    }
}

void work2(){
  for(int i=1;i<n;++i)
    for(int j=i+1;j<=i+45&&j<=n;++j){
      if(m[j]>=m[i]+k)
	update(dp2[j],dp1[i]+1);
      if(m[j]<=m[i]-k&&dp2[i]!=0)
	update(dp1[j],dp2[i]+1);
    }
}

int main(){
  fileopen();
  scanf("%d%d",&n,&k);
  for(int i=1;i<=n;++i)
    scanf("%lld",&m[i]);
  for(int i=1;i<=n;++i)
    dp1[i]=1;
  if(n<=10000)
    work1();
  else
    work2();
  printf("%d\n",best);
  fileclose();
  return 0;
}
