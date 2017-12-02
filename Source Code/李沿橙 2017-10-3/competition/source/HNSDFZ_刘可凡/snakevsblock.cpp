#include<bits/stdc++.h>
#define MAXN 205
#define INF 214748364
using namespace std;
inline char get_char(){
	static char buf[1000001],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int num=0;
	char c,sf=1;
	while(isspace(c=getchar()));
	if(c=='-') sf=-1,c=getchar();
	while(num=num*10+c-48,isdigit(c=getchar()));
	return num*sf;
}
int n;
int maps[MAXN][6];
bool no[MAXN][6];
struct P{
	int x,y,s,l,ly;
};
queue<P> mession;
int bfs(){
	int maxs=0;
	mession.push((P){1,3,0,4,3});
	while(!mession.empty()){
		P u=mession.front();
		mession.pop();
		if(u.x==n+1){
			if(u.s>maxs) maxs=u.s;
			continue;
		}
		P v=u;
		v.l+=maps[v.x+1][v.y];
		if(v.l<0){
			if(maxs<u.s) maxs=u.s;
		} else {
			v.s+=(maps[v.x+1][v.y]<0)?(-maps[v.x+1][v.y]):(0);
			v.x++;
			mession.push(v);
		}
		v=u;
		if(u.y>1&&!no[u.x][u.y-1]&&u.y-1!=u.ly){
			if((v.l+=maps[u.x][u.y-1])<0){
				if(maxs<u.s) maxs=u.s;
			} else {
				v.y=u.y-1;
				v.s=u.s+(maps[u.x][u.y-1]<0)?(-maps[u.x][u.y-1]):(0);
				v.ly=u.y;
				mession.push(v);
			}
		}
		v=u;
		if(u.y<5&&!no[u.x][u.y]&&u.y+1!=u.ly){
			if((v.l+=maps[u.x][u.y+1])<0){
				if(maxs<u.s) maxs=u.s;
			} else {
				v.y=u.y+1;
				v.s=u.s+(maps[u.x][u.y+1]<0)?(-maps[u.x][u.y+1]):(0);
				v.ly=u.y;
				mession.push(v);
			}
		}
	}
	return maxs;
}
int main(){
	freopen("snackvsblock.in","r",stdin),freopen("snackvsblock.out","w",stdout);
	n=read();
	srand(time(NULL));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=5;j++){
			maps[i][j]=read();
		}
	}
	int m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		no[x][y]=true;
	}
	//if(m==0) printf("8");
	//else printf("%d",rand()%n<<4);
	printf("%d",bfs());
	fclose(stdin),fclose(stdout);
	return 0;
}
