#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("stack.in","r",stdin);
    freopen("stack.out","w",stdout);
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
const int MOD=7;
int n,cnt_push,rmbuse;
int rmb[3001][1001];

inline void fmod(int &a){
  if(a>=MOD)
    a-=MOD;
}

void init(){
  for(int i=0;i<=3000;++i)
    for(int j=0;j<=1000;++j)
      rmb[i][j]=-1;
}

int dfs(int a){
  int ans=0;
  if(a>2*n){
    if(cnt_push==0)
      return 1;
    return 0;
  }
  if(rmb[2*n-a][cnt_push]!=-1)
    return rmb[2*n-a][cnt_push];
  if(cnt_push!=0){
    cnt_push--;
    ans+=dfs(a+1);
    fmod(ans);
    cnt_push++;
  }
  cnt_push++;
  ans+=dfs(a+1);
  fmod(ans);
  cnt_push--;
  rmb[2*n-a][cnt_push]=ans;
  ++rmbuse;
  return ans;
}

int main(){
  fileopen();
  init();
  scanf("%d",&n);
  printf("%d",dfs(1));
  fileclose();
  return 0;
}
