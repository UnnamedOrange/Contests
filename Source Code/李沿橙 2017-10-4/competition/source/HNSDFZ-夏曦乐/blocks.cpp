#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("blocks.in","r",stdin);
    freopen("blocks.out","w",stdout);
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
Memory Limit: 128MB
O2          : No
*/
int N,M;
int a[1000001];
ll qzh[1000001];

int work(int K){
  int ans=0;
  for(int i=1;i<=N-ans;++i)
    for(int j=N;j>=i+ans;--j)
      if(qzh[j]-qzh[i-1]-(ll)(j-i+1)*(ll)K>=0)
	ans=j-i+1;
  return ans;
}

int main(){
  fileopen();
  scanf("%d%d",&N,&M);
  for(int i=1;i<=N;++i){
    scanf("%d",&a[i]);
    qzh[i]=qzh[i-1]+a[i];
  }
  for(int i=1;i<=M;++i){
    int K;
    scanf("%d",&K);
    printf("%d ",work(K));
  }
  fileclose();
  return 0;
}
