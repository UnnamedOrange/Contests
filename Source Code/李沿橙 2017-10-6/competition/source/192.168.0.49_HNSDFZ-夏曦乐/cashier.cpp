#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("cashier.in","r",stdin);
    freopen("cashier.out","w",stdout);
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
const int INF=2111111111;
int T,best;
int a[25],b[25],u[25];

inline void eff(int s,int b){
  for(int i=s;i<=s+7;++i)
    a[i%24]-=b;
}

void work1(){
  for(int i=8;i<24;++i){
    if(a[i]>0){
      int needi=a[i];
      for(int j=i;j>=i-7;--j)
	if(b[j]>=needi){
	  b[j]-=needi;
	  u[j]+=needi;
	  eff(j,needi);
	  needi=0;
	  break;
	}else{
	  u[j]=b[j];
	  b[j]=0;
	  needi-=u[j];
	  eff(j,u[j]);
	}
      if(needi>0){
	printf("-1\n");
	return;
      }
    }
  }
  int sum=0;
  for(int i=0;i<24;++i)
    sum+=u[i];
  printf("%d\n",sum);
}

bool check(){
  for(int i=0;i<24;++i)
    if(a[i]>0)
      return false;
  return true;
}

void dfs(int dep,int cnt){
  if(cnt>=best)
    return;
  if(dep>23){
    if(check())
      best=cnt;
    return;
  }
  for(int i=0;i<=b[dep];++i){
    eff(dep,i);
    dfs(dep+1,cnt+i);
    eff(dep,-i);
  }
}

void work2(){
  best=INF;
  dfs(0,0);
  printf("%d\n",best);
}

int main(){
  fileopen();
  scanf("%d",&T);
  for(int t=1;t<=T;++t){
    for(int i=0;i<24;++i)
      scanf("%d",&a[i]);
    for(int i=0;i<24;++i)
      scanf("%d",&b[i]);
    init0(u);
    if(a[0]==0&&a[1]==0&&a[2]==0&&a[3]==0&&a[4]==0&&a[5]==0&&a[6]==0&&a[7]==0)
      work1();
    else
      work2();
  }
  fileclose();
  return 0;
}
