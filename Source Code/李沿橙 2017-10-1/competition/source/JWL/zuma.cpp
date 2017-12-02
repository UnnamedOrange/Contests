#include<cstdio>
#include<cstring>
const int maxn=210;
int n,ans;
int s[maxn][maxn],c[maxn],l[maxn];
char ch[maxn];
void dfs(int now,int x){
	if(now>=ans) return;
	int a;
	for(int i=0;i<l[now-x];i++){
		memset(s[now],0,sizeof(s[now]));
		a=3-s[now-x][i],s[now][i]=a;
		if(now+a>=ans) continue;
		for(int ii=0,jj=0;ii<l[now-x];ii++){
			s[now][jj]+=s[now-x][ii];
			if(s[now][jj]>2) s[now][jj]=0,jj--;
			jj++;
			l[now]=jj;
		}
		if(s[now][0]==0) dfs(now+a,a);
		else ans=now;
	}
}
int main(){
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	scanf("%s",ch);
	ans=n=strlen(ch);
	for(int i=0,j=0;i<n;){
		c[j]=ch[i]-'0';
		while(ch[i]-'0'==c[j]&&i<n) s[0][j]++,i++;
		if(s[0][j]>2) j--;
		j++;
		l[0]=j;
	}
	dfs(1,1);
	printf("%d\n",ans);
	return 0;
}
