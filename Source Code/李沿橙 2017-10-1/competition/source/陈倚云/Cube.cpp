#include <iostream> 
#include <cstdio> 
#include <fstream> 
#include <algorithm> 
#include <cmath> 
#include <deque> 
#include <vector> 
#include <queue> 
#include <string> 
#include <cstring> 
#include <map> 
#include <stack> 
#include <set> 
using namespace std;
const int mod=7;
const int maxn=30000;
inline int read(){
    int X=0,w=1; char ch=0;
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
int f[maxn],h[maxn],d[maxn];
using namespace std;
void pre(){for(int i=1;i<=maxn;i++){f[i]=i;h[i]=0;d[i]=1;}}
int find(int u){
	if(u==f[u]) return u;
	int tmp=f[u];
	f[u]=find(f[u]);
	h[u]+=h[tmp];
	return f[u];
}
int unite(int x,int y){
	f[x]=y;
	h[x]=d[y];
	d[y]=d[x]+d[y];
	d[x]=0;
}
int main(){
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int p,x,y;
	p=read();
	char c;
	pre();
	while(p>0){
		p--;
		cin >>c; 
		if(c=='M'){
			scanf("%d %d",&x,&y);
			int fx=find(x);
			int fy=find(y);
			if(fx!=fy) unite(fx,fy);
		}
		else{
			scanf("%d",&x);
			printf("%d\n",h[x]);
		}
	}
	return 0;
}
