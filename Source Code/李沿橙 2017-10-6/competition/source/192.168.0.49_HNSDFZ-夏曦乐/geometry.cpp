#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("geometry.in","r",stdin);
    freopen("geometry.out","w",stdout);
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
int n,m,xp,yp;
int x[100001],y[100001];

bool check(int a){
  ll num=xp;
  num*=y[a];
  num/=x[a];
  num=-num;
  num+=y[a];
  if(num<=yp)
    return true;
  return false;
}

int SPcheck(int lef,int rig){
  for(int i=lef;i<=rig;++i)
    if(!check(i))
      return i-1;
  return rig;
}

int erf(int lef,int rig){
  if(rig-lef<=5)
    return SPcheck(lef,rig);
  int mid=(lef+rig)/2;
  if(check(mid))
    return erf(mid,rig);
  else
    return erf(lef,mid-1);
}

int main(){
  fileopen();
  scanf("%d",&n);
  for(int i=1;i<=n;++i)
    scanf("%d",&x[i]);
  for(int i=1;i<=n;++i)
    scanf("%d",&y[i]);
  sort(x+1,x+n+1);
  sort(y+1,y+n+1);
  scanf("%d",&m);
  for(int i=1;i<=m;++i){
    scanf("%d%d",&xp,&yp);
    printf("%d\n",erf(1,n));
  }
  fileclose();
  return 0;
}
