#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("general.in","r",stdin);
    freopen("general.out","w",stdout);
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
int n,k,t;
struct station{
  vector<int> r;
  int size,fa,dep;
  bool ard;
}s[100001];

void work1(){
  queue<int> e1;
  int ans=0;
  for(int i=1;i<=n;++i){
    s[i].size=s[i].r.size();
    s[i].ard=false;
    if(s[i].size==1)
      e1.push(i);
  }
  while(!e1.empty()){
    int me=e1.front();
    e1.pop();
    if(s[me].ard)
      continue;
    int fa;
    for(vi i=s[me].r.begin();i!=s[me].r.end();++i)
      if(s[*i].size>0){
	fa=*i;
	break;
      }
    for(vi i=s[fa].r.begin();i!=s[fa].r.end();++i){
      s[*i].ard=true;
      for(vi j=s[*i].r.begin();j!=s[*i].r.end();++j){
	s[*j].size--;
	if(s[*j].size==1&&(*j)!=fa)
	  e1.push(*j);
      }
    }
    ++ans;
  }
  printf("%d\n",ans);
}

void build_tree(int node,int f,int deep){
  s[node].fa=f;
  s[node].dep=deep;
  s[node].ard=false;
  for(vi i=s[node].r.begin();i!=s[node].r.end();++i)
    if((*i)!=f)
      build_tree(*i,node,deep+1);
}

int found_dep(){
  int est_dep=0,est_s=0;
  for(int i=1;i<=n;++i)
    if(s[i].ard==false&&s[i].dep>est_dep){
      est_dep=s[i].dep;
      est_s=i;
    }
  return est_s;
}

int dfs(int come,int now,int dep){
  if(dep>k)
    return 0;
  int sum=s[now].ard==false?1:0;
  s[now].ard=true;
  for(vi i=s[now].r.begin();i!=s[now].r.end();++i)
    if((*i)!=come)
      sum+=dfs(now,*i,dep+1);
  return sum;
}

void work2(){
  int best=2111111111;
  for(int i=1;i<=n;++i){
    int acted=0,ans=0;
    build_tree(i,0,1);
    while(acted<n){
      int deep=found_dep();
      for(int j=1;j<=k&&s[deep].fa!=0;++j)
	deep=s[deep].fa;
      acted+=dfs(0,deep,0);
      ++ans;
      if(ans>=best)
	break;
    }
    if(ans<best)
      best=ans;
  }
  printf("%d\n",best);
}

int main(){
  fileopen();
  scanf("%d%d%d",&n,&k,&t);
  if(k==0){
    printf("%d\n",n);
    fileclose();
    return 0;
  }
  for(int i=1;i<n;++i){
    int u,v;
    scanf("%d%d",&u,&v);
    s[u].r.push_back(v);
    s[v].r.push_back(u);
  }
  if(k==1)
    work1();
  else
    work2();
  fileclose();
  return 0;
}
