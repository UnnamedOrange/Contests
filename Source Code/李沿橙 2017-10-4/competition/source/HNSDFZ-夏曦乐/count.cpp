#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("count.in","r",stdin);
    freopen("count.out","w",stdout);
  }
}
inline void fileclose(){
  if(FileIO){
    fclose(stdin);
    fclose(stdout);
  }
}
/*
Time Limit  : 1.5sec
Memory Limit: 128MB
O2          : No
*/
const int MOD=998244353;
int L,R,k,ans;

int fpow(int a1,int b1){
  ll a=a1,b=b1,c=1;
  while(b){
    if(b&1)
      c=c*a%MOD;
    a=a*a%MOD;
    b>>=1;
  }
  return (int)c;
}

inline void modder(int &a){
  if(a>=MOD)
    a-=MOD;
}

int main(){
  fileopen();
  scanf("%d%d%d",&L,&R,&k);
  if(L==1){
    ans+=fpow(2,k);
    modder(ans);
    L=2;
  }
  for(int i=L;i<=R;++i){
    ans+=fpow(i,k);
    modder(ans);
  }
  printf("%d\n",ans);
  fileclose();
  return 0;
}
