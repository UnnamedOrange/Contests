#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("cube.in","r",stdin);
    freopen("cube.out","w",stdout);
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
int p;
struct stacker{
  int nxt,pre;
  int nxtsize;
}s[30001];

char reader(){
  char c=getchar();
  while(true){
    if(c=='M')
      return 'M';
    if(c=='C')
      return 'C';
    c=getchar();
  }
}

int find_bot(int a){
  while(s[a].nxt)
    a=s[a].nxt;
  return a;
}

int get_bot_size(int a){
  int cnt=0;
  for(;s[a].nxt;a=s[a].nxt)
    cnt+=s[a].nxtsize;
  return cnt;
}

int find_top(int a){
  while(s[a].pre)
    a=s[a].pre;
  return a;
}

void M(int x,int y){
  int xb=find_bot(x),yt=find_top(y),yb=find_bot(y),xbs=get_bot_size(x),ybs=get_bot_size(yt);
  s[xb].nxt=yt;
  s[yt].pre=xb;
  s[xb].nxtsize=1;
  s[x].nxt=yb;
  s[x].nxtsize=xbs+ybs+1;
}

int main(){
  fileopen();
  scanf("%d",&p);
  for(int P=1;P<=p;++P){
    char c=reader();
    if(c=='M'){
      int a,b;
      scanf("%d%d",&a,&b);
      M(a,b);
    }else{
      int a;
      scanf("%d",&a);
      printf("%d\n",get_bot_size(a));
    }
  }
  fileclose();
  return 0;
}
