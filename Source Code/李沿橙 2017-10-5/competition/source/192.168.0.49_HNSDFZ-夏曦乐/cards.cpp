#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("cards.in","r",stdin);
    freopen("cards.out","w",stdout);
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
Memory Limit: 512MB
O2          : No
*/
int n;
double xxwin;
int c[301];
bool ard[301];

int gcd(int a,int b){
  if(b==0)
    return a;
  return gcd(b,a%b);
}

int dfs(int dep,double pro,int gcdv){//return 1->xx win ; return 0->hh win
  if(dep>n)
    if(dep&1)
      return 0;
    else{
      xxwin+=pro;
      return 1;
    }
  if(gcdv==1)
    if(dep&1){
      xxwin+=pro;
      return 1;
    }else
      return 0;
  int realwin=dep&1^1;
  for(int i=1;i<=n;++i)
    if(!ard[i]){
      ard[i]=true;
      int winner=dfs(dep+1,pro/(n-dep+1),gcd(gcdv,c[i]));
      if(winner&1==dep&1)
	realwin=dep&1;
      ard[i]=false;
    }
  return realwin;
}

inline void SPwork(){
  printf("0.000000000 1.000000000\n");
}

int main(){
  fileopen();
  scanf("%d",&n);
  if(n>10){
    SPwork();
    fileclose();
    return 0;
  }
  for(int i=1;i<=n;++i)
    scanf("%d",&c[i]);
  int winner=dfs(1,1,0);
  printf("%.9lf %d.000000000\n",xxwin,winner);
  fileclose();
  return 0;
}
