#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("zuma.in","r",stdin);
    freopen("zuma.out","w",stdout);
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
const int INF=2111111111;
char s[201];
int balls[210];
int best=INF;

void work1(){
  char now=s[0];
  int size=1,p=1;
  for(int i=1;i<strlen(s);++i)
    if(s[i]==now)
      ++size;
    else{
      balls[p]=size;
      ++p;
      size=1;
      now=s[i];
    }
}

void insert_ball(int a){
  balls[a]++;
  int i=0,j;
  if(balls[a]>3)
    for(i=1;a-i>=1&&balls[a+i]!=0;++i){
      balls[a-i]+=balls[a+i];
      if(balls[a-i]<3)
	break;
    }
  for(j=a-i;balls[j+i+1]!=0;++j)
    balls[j]=balls[j+i+1];
  for(int k=j;k<=200;++k)
    balls[k]=0;
}

void dfs(int dep){
  if(dep>=best)
    return;
  if(balls[1]==0){
    best=dep;
    return;
  }
  int ballen[201];
  for(int i=1;i<=200;++i)
    ballen[i]=balls[i];
  for(int i=1;balls[i]!=0;++i){
    insert_ball(i);
    dfs(dep+1);
    for(int i=1;i<=200;++i)
      balls[i]=ballen[i];
  }
}

int main(){
  fileopen();
  scanf("%s",s);
  work1();
  dfs(1);
  printf("%d",best);
  fileclose();
  return 0;
}
