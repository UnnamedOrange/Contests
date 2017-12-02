#include <bits/stdc++.h>
using namespace std;
typedef long long lol;
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-') y=1;c=getchar();}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';c=getchar();}
		return x*y;	
}
lol n,k,num,a[1000010],sum,g,b[1000010];lol step=0;
void read1(lol nbe,lol weishu){
	memset(a,0,sizeof(a));
	for(int i=weishu;i>=1;i--){
		a[i]=nbe%10;nbe=nbe/10;
		if(a[i]==3) b[sum++]=i;
		}		
}
void work(){
for(int i=1;i<=n;i++)
if(a[i]==2&&a[i+1]==3) {
	if(i%2!=0) a[i+1]=2;
	else a[i]=3;
	break;}}
int main(){
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(scanf("%d%d",&n,&k)!=EOF){
	sum=0;memset(b,0,sizeof(b));
	num=read();read1(num,n);
	for(int i=1;i<=k;i++)	work();
	for(int i=1;i<=n;i++)
	cout<<a[i];cout<<endl;	}	
	return 0;
}
