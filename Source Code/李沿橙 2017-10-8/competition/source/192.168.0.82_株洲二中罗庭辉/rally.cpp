#include <bits/stdc++.h>
typedef long long lol;
using namespace std;
struct cnm{
	lol x;lol y;
}f1[500][500];
int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}
	return x*y;		
}
lol n,m,k,f[500][500],ans[500][500],num;
void search(lol x,lol y){
lol ans1=f[x][y],tx=x,ty=y;
	for(int i=y+1;i<=m;i++)
{ans1=ans1+f[tx][i];
if(ans1%k==0) ans[x][y]++;}ans1=f[x][y];//xiang you
for(int i=y+1;i<=n;i++)
{ans1+=f[x][i];
if(ans1%k==0) ans[x][y]++;}ans1=f[x][y];//xiangxia
lol sum=0;
if(tx+1<=n&&ty+1<=m)
while(tx<=n&&ty<=m){
if(sum==0) tx=tx+1,ty=ty+1,sum++;
else tx++;
ans1+=f1[tx][ty].x+f1[tx][ty].y-f[tx][ty];
if(ans1%k==0) ans[x][y]++;
lol ans2=ans1;
for(int i=ty+1;i<=m;i++)
{ans2+=f1[tx][ty].y;
if(ans2%k==0) ans[x][y]++;}
if(tx+1>n) break;
}
}
int main(){
	freopen("rally.in","r",stdin);
	freopen("rally.out","w",stdout);
	lol anss=0;
	n=read();m=read();k=read();
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
{f[i][j]=read();if(f[i][j]%k==0) ans[i][j]=1;}
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
	lol num1=0,num2=0,ti=i,tj=j;
	while(tj!=0){
	num1+=f[ti][tj];tj--;}
	ti=i,tj=j;
	while(ti!=0){
	num2=f[ti][tj]+num2;ti--;}
		f1[i][j].x=num1;f1[i][j].y=num2;
	}
//quanbuyiyang
for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		search(i,j);
		for(int i=1;i<=n;i++)	
			for(int j=1;j<=m;j++)
			anss+=ans[i][j];
	cout<<anss<<endl;		
	return 0;
}
