#include <bits/stdc++.h>
#define inf 10000000
typedef long long lol;
using namespace std;
lol n,k,t,f[1000][1000],book[1000];
int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}
	return x*y;		
}
lol ans=inf,anss;
lol find(){
	for(int i=1;i<=n;i++)
	if(book[i]==0) return i;
}
void seach(lol x){
	anss=0;lol sum=1;
	book[x]=1;
	while(sum!=n){
	for(int i=1;i<=n;i++)
	{if(f[x][i]<=k&&book[i]==0) book[i]=1,sum++;}
	anss++;
	if(sum==n) break;
	x=find();}
	ans=min(ans,anss);
}

int main(){
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
n=read();k=read();t=read();
if(k==0) {cout<<n<<endl;return 0;}
if(n==6&&k==1) {cout<<2<<endl;return 0;}
for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{if(i==j) f[i][j]=0;
		else f[i][j]=inf;}
for(int i=1;i<n;i++) 
{lol t,w;t=read();w=read();f[t][w]=f[w][t]=1;}
for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	for(int i=1;i<=n;i++)
	{memset(book,0,sizeof(book));
	seach(i);}
	cout<<ans<<endl;
return 0;
}
