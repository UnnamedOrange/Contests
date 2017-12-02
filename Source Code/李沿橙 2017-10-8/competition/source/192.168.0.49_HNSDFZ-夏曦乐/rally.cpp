#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("rally.in","r",stdin);
    freopen("rally.out","w",stdout);
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
int n,m,K,ans;
int mat[401][401],sum[401],kk[401];

void work(){
  for(int i=1;i<=m;++i){
    init0(sum);
    for(int j=i;j<=m;++j){
      init0(kk);
      for(int k=1;k<=n;++k)
	kk[k]=kk[k-1]+mat[j][k];
      for(int k=1;k<=n;++k)
	sum[k]+=kk[k];
      for(int k=1;k<=n;++k)
	for(int l=k;l<=n;++l)
	  if((sum[l]-sum[k-1])%K==0)
	    ++ans;
    }
  }
}

int main(){
  fileopen();
  scanf("%d%d%d",&n,&m,&K);
  int last=-1;
  for(int j=1;j<=n;++j)
    for(int i=1;i<=m;++i)
      scanf("%d",&mat[i][j]);
  work();
  printf("%d\n",ans);
  fileclose();
  return 0;
}
