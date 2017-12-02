#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("biology.in","r",stdin);
    freopen("biology.out","w",stdout);
  }
}
inline void fileclose(){
  if(FileIO){
    fclose(stdin);
    fclose(stdout);
  }
}
/*
Time Limit  : 2sec
Memory Limit: 256MB
O2          : No
*/
int N,M,cntgen;
string s[100001];
struct trie{
  trie *e[26];
  int dep,act;
}*root,*acting;

inline int t(char c){
  return c-'a';
}

void add_to_tries(int num){
  int len=s[num].length();
  trie *p=root;
  for(int i=len-1;i>=0;--i){
    if(p->e[t(s[num][i])]==NULL){
      p->e[t(s[num][i])]=new trie;
      p->e[t(s[num][i])]->dep=p->dep+1;
    }
    p=p->e[t(s[num][i])];
  }
}

inline void work1(){
  ++cntgen;
  cin>>s[cntgen];
  add_to_tries(cntgen);
}

void acted(int a){
  int len=s[a].length();
  trie *p=root;
  for(int i=len-1;i>=0;--i){
    p->act=1;
    p=p->e[t(s[a][i])];
  }
  p->act=2;
  acting=p;
}

void reacted(int a){
  int len=s[a].length();
  trie *p=root;
  for(int i=len-1;i>=0;--i){
    if(p->e[t(s[a][i])]->act==0){
      p->act=2;
      acting=p;
    }
    if(p->e[t(s[a][i])]->act==2)
      return;
    p=p->e[t(s[a][i])];
  }
}

void work2(){
  int T,a;
  acting=NULL;
  scanf("%d%d",&T,&a);
  for(int i=2;i<=T;++i){
    scanf("%d",&a);
    reacted(a);
  }
  printf("%d",acting->dep);
}   

int main(){
  fileopen();
  scanf("%d%d",&N,&M);
  root=new trie;
  for(int i=1;i<=N;++i){
    cin>>s[i];
    add_to_tries(i);
  }
  cntgen=N;
  for(int i=1;i<=M;++i){
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
