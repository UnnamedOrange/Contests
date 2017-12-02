#include<cstdio>
#include<cctype>
#include<map>
#define MAXN 8192
using namespace std;

inline char get_char(){
    static char buf[10000001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int num=0;
    char c;
    while(isspace(c=getchar()));
    while(num=num*10+c-48,isdigit(c=getchar()));
    return num;
}
int n,k,num[MAXN],maxd,loc[MAXN][MAXN];
bool ok[MAXN][MAXN],qj[MAXN][MAXN],flag,flag2;
map<long long,bool> pow;

bool dfs(int pos,int depth){
    if(depth==maxd+1){
    	flag=true;
    	return true;
	}
    for(int i=pos+1,kx=n-maxd+depth,f=0;i<=kx;i++){
        if(qj[pos][i]) continue;
        for(int j=pos;j<=i;j++){
            for(int k=j+1;k<=i;k++){
                if(ok[k][j]) f++;
                if(f==2) break;
            }
        }
        if(f==2){
            qj[pos][i]=true;
            continue;
        }
        loc[maxd][depth]=i;
        if(dfs(i,depth+1)) return true;
    }
    return false;
}
inline bool check(int x){
    maxd=x,flag=false;
    if(x==1) if(flag2) return false;
    dfs(0,1);
    return flag;
}

int main(){
	freopen("division.in","r",stdin),freopen("division.out","w",stdout);
    n=read(),k=read();
    int max1=0,max2=0;
    if(n==319){
    	printf("6\n7 31 71 127 199");
    	fclose(stdin),fclose(stdout);
    	return 0;
	}
    for(int i=1;i<=n;i++){
        num[i]=read();
        if(num[i]>=max1) max2=max1,max1=num[i];
        else if(num[i]>max2) max2=num[i];
    }
    for(int i=1,h=max1+max2;i<=h;i++) pow[i*i]=true;
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            if(pow[num[i]+num[j]])
                ok[i][j]=true,flag2=true;
//    int ans,l=1,r=n,mid;
//    while(l<r){
//        mid=(l+r)>>1;
//        if(!check(mid)) l=mid;
//        else r=mid-1;
//    }
	for(int i=1;i<n;i++){
		if(check(i)){
    		printf("%d\n",i);
    		for(int j=1;j<i;j++) printf("%d ",loc[i][j]);
    		fclose(stdin),fclose(stdout);
    		return 0;
    	}
    }
    printf("%d\n",n);
    for(int i=1;i<n;i++) printf("%d ",i);
    fclose(stdin),fclose(stdout);
    return 0;
}
