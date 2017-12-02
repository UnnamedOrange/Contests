#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("trans.in","r",stdin);
    freopen("trans.out","w",stdout);
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
O2          : Yes
*/
int n,k;
int d[1000001];
stack<int> s;

inline int reader(){
  char c=getchar();
  while(c<'0'||c>'9')
    c=getchar();
  return c-'0';
}

void work(){
  int cnt=0;
  while(!s.empty()){
    int ms=s.top();
    s.pop();
    if(ms&1){
      d[ms+1]=2;
      if(ms+2<=n&&d[ms+2]==3)
	s.push(ms+1);
    }else{
      d[ms]=3;
      if(d[ms-1]==2)
	s.push(ms-1);
    }
    ++cnt;
    if(cnt==k||(cnt>=9000000&&((cnt&1)==(k&1)))){
      while(!s.empty())
	s.pop();
      return;
    }
  }
  return;
}

int main(){
  fileopen();
  while(scanf("%d%d",&n,&k)!=EOF){
    for(int i=1;i<=n;++i)
      d[i]=reader();
    for(int i=n;i>1;--i)
      if(d[i]==3&&d[i-1]==2)
	s.push(i-1);
    work();
    for(int i=1;i<=n;++i)
      printf("%d",d[i]);
    printf("\n");
  }
  fileclose();
  return 0;
}
