#include<bits/stdc++.h>
#define ll long long int
#define init0(a) memset(a,0,sizeof(a))
#define FileIO true
using namespace std;
inline void fileopen(){
  if(FileIO){
    freopen("reverse.in","r",stdin);
    freopen("reverse.out","w",stdout);
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
const int INF=2111111111;
char s[100001];
int cost1[100001],cost2[100001];
int len,best=INF;

int main(){
  fileopen();
  scanf("%s",s);
  len=strlen(s);
  if(s[0]=='1')
    cost1[0]=1;
  if(s[len-1]=='0')
    cost2[len-1]=1;
  for(int i=1;i<len;++i)
    if(s[i]=='0')
      cost1[i]=cost1[i-1];
    else
      cost1[i]=cost1[i-1]+1;
  for(int i=len-1;i>=0;--i)
    if(s[i]=='1')
      cost2[i]=cost2[i+1];
    else
      cost2[i]=cost2[i+1]+1;
  best=cost2[0];
  best=min(best,cost1[len-1]);
  for(int i=0;i<len;++i)
    best=min(best,cost1[i]+cost2[i+1]);
  printf("%d\n",best);
  fileclose();
  return 0;
}
