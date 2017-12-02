#include<cstdio>
const int mod=1e9+7;
const int maxn=1e5+10;
inline int max_(int x,int y){return x>y?x:y;}
int n;
int s[maxn],fa[maxn],sz[maxn];
int f[maxn][3];
int u[maxn],v[maxn];
int h[maxn],hs;
int et[maxn],en[maxn];
int cz[maxn],ans[maxn];
int find_f(int k){return k==fa[k]?k:fa[k]=find_f(fa[k]);}
void add(int s,int t){hs++,et[hs]=t,en[hs]=h[s],h[s]=hs;}
int niyuan(int x,int y){
	int ret=1;
	while(y){
		if(y&1) ret=(1ll*x*ret)%mod;;
		x=(1ll*x*x)%mod;
		y>>=1;
	}
	return ret;
}
int ff[maxn];
void dfs(int k,int fat){
	ff[k]=fat;
	f[k][0]=s[k],f[k][1]=f[k][2]=0;
	for(int i=h[k];i;i=en[i])
	if(et[i]!=fat){
		dfs(et[i],k);
		if(f[et[i]][1]+s[et[i]]>f[k][1]){
			f[k][1]=f[et[i]][1]+s[et[i]];
		}
		else if(f[et[i]][1]+s[et[i]]>f[k][2]){
			f[k][2]=f[et[i]][1]+s[et[i]];
		}
		if(f[et[i]][2]) f[k][2]=max_(f[k][2],f[et[i]][2]+s[et[i]]);
		f[k][0]=max_(f[k][0],f[et[i]][0]);
	}
	f[k][0]=max_(f[k][0],f[k][1]+f[k][2]+s[k]);
}
int main(){
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	for(int i=1;i<n;i++) scanf("%d%d",&u[i],&v[i]);
	for(int i=1;i<n;i++) scanf("%d",&cz[i]);
	ans[n]=1;
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1,f[i][0]=s[i],ans[n]=(1ll*ans[n]*s[i])%mod;
	int a,b,c;
	bool ok;
	for(int i=n-1;i>0;i--){
		a=u[cz[i]],b=v[cz[i]],ok=0;
		if(!ff[a]) a^=b,b^=a,a^=b;
		if(!ff[b]) ok=1;
		if(!ok&&sz[find_f(a)]<sz[find_f(b)]) a^=b,b^=a,a^=b;
		ans[i]=ans[i+1];
		ans[i]=(1ll*ans[i]*niyuan(f[find_f(a)][0],mod-2))%mod;
		ans[i]=(1ll*ans[i]*niyuan(f[find_f(b)][0],mod-2))%mod;
		add(a,b),add(b,a),ff[b]=a;
		sz[find_f(a)]+=sz[find_f(b)];
		fa[find_f(b)]=find_f(a);
		if(!ok) dfs(b,a);
		for(int j=a,k=b;j;k=j,j=ff[j]){
			if(f[k][1]+s[k]>f[j][1]){
				f[j][1]=f[k][1]+s[k];
			}
			else if(f[k][1]+s[k]>f[j][2]){
				f[j][2]=f[k][1]+s[k];
			}
			if(f[k][2]) f[j][2]=max_(f[j][2],f[k][2]+s[k]);
			c=max_(f[k][0],f[j][1]+f[j][2]+s[j]);
			if(c>f[j][0]) f[j][0]=c;
			else break;
		}
		ans[i]=(1ll*ans[i]*f[find_f(a)][0]);
	}
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
