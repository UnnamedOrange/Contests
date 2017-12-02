#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
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
typedef vector<int>::iterator vi;
int n,m;
vector<int> color[300001];
pair<int,int> rw[300001];

void work1(){
  int l,r,c;
  scanf("%d%d%d",&l,&r,&c);
  vi p=lower_bound(color[c].begin(),color[c].end(),l);
  vi q=upper_bound(color[c].begin(),color[c].end(),r);
  cout<<q-p<<endl;
}

void work2(){
  int x;
  scanf("%d",&x);
  pair<int,int> xx=rw[x],xxp=rw[x+1];
  if(xx.first==xxp.first)
    return;
  color[xx.first][xx.second-1]++;
  color[xxp.first][xxp.second-1]--;
  rw[x+1]=xx;
  rw[x]=xxp;
}

int main(){
  fileopen();
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;++i){
    int a;
    scanf("%d",&a);
    color[a].push_back(i);
    rw[i]=make_pair(a,color[a].size());
  }
  for(int i=1;i<=m;++i){
    int cmd;
    scanf("%d",&cmd);
    if(cmd==1)
      work1();
    else
      work2();
  }
  fileclose();
  return 0;
}
