#include <bits/stdc++.h>
#define lol long long
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,m;
int x[100005],y[100005];
int ef(lol qx,lol qy,int left,int right)
{	
	if(left==right-1)return left;
	int midd=(right+left)/2;
	lol a=x[midd]*y[midd],b=x[midd]*qy,c=y[midd]*qx;
	if(a==(b+c))return midd;
	if(a>(b+c))return ef(qx,qy,left,midd);
	if(a<(b+c))return ef(qx,qy,midd,right);
}
int main(){
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)x[i]=read();
	for(int i=1;i<=n;i++)y[i]=read();
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	m=read();
	for(int i=1;i<=m;i++){
		int quanx=read(),quany=read(),ans;
		ans=ef(quanx,quany,0,n+1);
		printf("%d\n",ans);
	}
	return 0;
}
