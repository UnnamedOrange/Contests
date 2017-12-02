#include<cstdio>
#include<cstring>
const int maxn=1e5+10;
inline int min_(int x,int y){return x<y?x:y;}
int n,ans;
char ch[maxn];
int t[maxn],d[maxn];
int main(){
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%s",1+ch);
	ans=n=strlen(1+ch);
	for(int i=1;i<=n;i++) t[i]=t[i-1]+(ch[i]=='1'?1:0);
	for(int i=n;i>=1;i--) d[i]=d[i+1]+(ch[i]=='0'?1:0);
	for(int i=0;i<=n;i++) ans=min_(ans,t[i]+d[i+1]);
	printf("%d",ans);
	return 0;
}
