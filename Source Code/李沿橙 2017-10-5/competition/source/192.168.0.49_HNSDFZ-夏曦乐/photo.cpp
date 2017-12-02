#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("photo.in","r",stdin);
    freopen("photo.out","w",stdout);
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
const int MOD=1000000007;
int n,m,k,ans;
int photo[11][11];

inline void modder(int &a){
  if(a>=MOD)
    a-=MOD;
}

void check(){
  bool coloruse1[2001]={0},coloruse2[2001]={0};
  int colorcnt1=0,colorcnt2=0;
  int colors[2001]={0},colort[2001]={0};
  for(int i=1;i<=m;++i){
    for(int j=1;j<=n;++j)
      if(!coloruse1[photo[j][i]]){
	coloruse1[photo[j][i]]=true;
	++colorcnt1;
      }
    colors[i]=colorcnt1;
  }
  for(int i=m;i>=1;--i){
    for(int j=1;j<=n;++j)
      if(!coloruse2[photo[j][i]]){
	coloruse2[photo[i][j]]=true;
	++colorcnt2;
      }
    colort[i]=colorcnt2;
  }
  for(int i=1;i<m;++i)
    if(colors[i]!=colort[i+1])
      return;
  modder(++ans);
}

void dfs(int x,int y){
  if(x>n){
    if(y==m){
      check();
      return;
    }
    dfs(1,y+1);
    return;
  }
  for(int i=1;i<=k;++i){
    photo[x][y]=i;
    dfs(x+1,y);
  }
}

int main(){
  fileopen();
  scanf("%d%d%d",&n,&m,&k);
  dfs(1,1);
  printf("%d\n",ans);
  fileclose();
  return 0;
}
