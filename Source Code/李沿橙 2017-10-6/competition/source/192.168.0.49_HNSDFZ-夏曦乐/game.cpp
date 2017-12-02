#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
  }
}
inline void fileclose(){
  if(FileIO){
    fclose(stdin);
    fclose(stdout);
  }
}
/*
Time Limit  : 3sec
Memory Limit: 512MB
O2          : Yes
*/
const int MOD=1000000007;
int n,m,sum;
int ba[50001];

void c1(){
  int a,b,c;
  scanf("%d%d%d",&a,&b,&c);
  for(int i=a;i<=b;++i)
    ba[i]+=c;
}

void c2(){
  int a,b;
  scanf("%d%d",&a,&b);
  for(int i=a;i<=b;++i)
    ba[i]=-ba[i];
}

void dfs(int s,int e,int n,int f,ll ans){
  if(n==f){
    sum+=ans;
    sum%=MOD;
    return;
  }
  if(s>e)
    return;
  dfs(s+1,e,n+1,f,ans*ba[s]%MOD);
  dfs(s+1,e,n,f,ans);
}
  

void c3(){
  int a,b,k;
  scanf("%d%d%d",&a,&b,&k);
  sum=0;
  dfs(a,b,0,k,1);
  printf("%d\n",sum<0?sum+MOD:sum);
}

int main(){
  fileopen();
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;++i)
    scanf("%d",&ba[i]);
  for(int i=1;i<=m;++i){
    int cmd;
    scanf("%d",&cmd);
    if(cmd==1)
      c1();
    if(cmd==2)
      c2();
    if(cmd==3)
      c3();
  }
  fileclose();
  return 0;
}
