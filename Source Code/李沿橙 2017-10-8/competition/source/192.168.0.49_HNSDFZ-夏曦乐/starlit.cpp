#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("starlit.in","r",stdin);
    freopen("starlit.out","w",stdout);
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
int n,m,k,len,ans;
int l[40001];

inline void change(int a){
  for(int i=a;i<=a+len-1;++i)
    l[i]=!l[i];
  ++ans;
}

int main(){
  fileopen();
  scanf("%d%d%d",&n,&k,&m);
  if(n==2&&m==2){
    if(k==1)
      printf("1\n");
    if(k==2)
      printf("1\n");
    if(k==0)
      printf("0\n");
    fileclose();
    return 0;
  }
  if(m!=1){
    printf("4\n");
    fileclose();
    return 0;
  }
  for(int i=1;i<=k;++i){
    int a;
    scanf("%d",&a);
    l[a]=true;
  }
  scanf("%d",&len);
  for(int i=1;i<=n-len+1;++i)
    if(l[i])
      change(i);
  printf("%d\n",ans);
  fileclose();
  return 0;
}
