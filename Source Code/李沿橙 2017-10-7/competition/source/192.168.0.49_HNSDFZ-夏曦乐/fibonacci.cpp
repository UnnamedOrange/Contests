#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("fibonacci.in","r",stdin);
    freopen("fibonacci.out","w",stdout);
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
O2          : Yes
*/
ll fib[60];
int m;

inline void fibonacci(){
  fib[0]=1;
  fib[1]=1;
  for(int i=2;i<60;++i)
    fib[i]=fib[i-1]+fib[i-2];
}

inline void jump(ll &a){
  ll *p=lower_bound(fib+1,fib+60,a);
  p--;
  a=a-*p;
}

ll work(ll a,ll b){
  stack<ll>ma,mb;
  while(a!=1){
    ma.push(a);
    jump(a);
  }
  while(b!=1){
    mb.push(b);
    jump(b);
  }
  if(ma.empty()||mb.empty())
    return 1;
  ll lca=1,sa=ma.top(),sb=mb.top();
  ma.pop();
  mb.pop();
  while(sa==sb){
    lca=sa;
    if(ma.empty()||mb.empty())
      return lca;
    sa=ma.top();
    sb=mb.top();
    ma.pop();
    mb.pop();
  }
  return lca;
}

int main(){
  fileopen();
  fibonacci();
  scanf("%d",&m);
  while(m--){
    ll a,b;
    scanf("%lld%lld",&a,&b);
    printf("%lld\n",work(a,b));
  }
  fileclose();
  return 0;
}
