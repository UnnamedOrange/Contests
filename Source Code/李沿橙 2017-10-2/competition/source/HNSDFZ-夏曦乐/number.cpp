#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("number.in","r",stdin);
    freopen("number.out","w",stdout);
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
int n;
int num[2][2][2][2][2][2][2][2][2][2];

void join(int a){
  int m[10]={0};
  while(a!=0){
    m[a%10]=1;
    a/=10;
  }
  num[m[0]][m[1]][m[2]][m[3]][m[4]][m[5]][m[6]][m[7]][m[8]][m[9]]++;
}

void work(){
  ll ans=0;
  for(int a0=0;a0<=1;++a0)
    for(int a1=0;a1<=1;++a1)
      for(int a2=0;a2<=1;++a2)
	for(int a3=0;a3<=1;++a3)
	  for(int a4=0;a4<=1;++a4)
	    for(int a5=0;a5<=1;++a5)
	      for(int a6=0;a6<=1;++a6)
		for(int a7=0;a7<=1;++a7)
		  for(int a8=0;a8<=1;++a8)
		    for(int a9=0;a9<=1;++a9){
		      int m=num[a0][a1][a2][a3][a4][a5][a6][a7][a8][a9];
		      ans+=m*(m-1)/2;
		    }
  printf("%lld\n",ans);
}

int main(){
  fileopen();
  scanf("%d",&n);
  for(int i=1;i<=n;++i)
    join(i);
  work();
  fileclose();
  return 0;
}
