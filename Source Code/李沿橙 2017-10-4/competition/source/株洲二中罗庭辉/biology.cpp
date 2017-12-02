#include <bits/stdc++.h>
typedef long long lol;
using namespace std;
inline int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=1;c=getchar();}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';c=getchar();}
			return x*y;
}
lol n,m,anss;int a[100];char c[1000000];string s[100000];int pos;
struct cmp{
	string s;
	int lon;
	int tail;
}e[1000001];
struct cnm{
	string s;
}po[1000001];
inline	void  compare(int id){
	string s2;s2=e[id].s;
	string st;st=po[pos].s;
	pos++;
	lol lens=st.size();
	int weishu=0;
   if(e[id].lon>=lens)
   for(int i=0;i<lens;i++)
   	{int j=e[id].lon-1-lens;
   		if(st[i]==s2[j]) {j++;po[pos].s[weishu++]=s2[j];}
   		else break;
   	}
   else {
   for(int i=0;i<e[id].lon;i++)
   	{int j=lens-1-e[id].lon;
   		if(s2[i]==st[i]) {j++;po[pos].s[weishu++]=s2[i];}
   		else break;
   	}}   	
}
inline void work(){
	 pos=1;
	memset(a,0,sizeof(a));memset(c,0,sizeof(c));
	lol num=read();
	for(int i=1;i<=num;i++) a[i]=read();
	po[pos].s=e[a[1]].s;
	for(int i=2;i<=num;i++)
	compare(a[i]);
}                  
int main(){
freopen("biology.in","r",stdin);
freopen("biology.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{cin>>e[i].s;string s1;s1=e[i].s;lol len=s1.size();
	e[i].lon=len;}
for(int i=1;i<=m;i++){
		int t;t=read();
		if(t==2) {anss=0;work();anss=s[pos].size();cout<<anss<<endl;}
		else {n++;cin>>e[n].s;}
	}
	return 0;
}
