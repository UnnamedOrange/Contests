#include<bits/stdc++.h>
using namespace std;
#define maxn 505
#define mod 1000000007
int p[]={2,3,5,7,11,13,17,19};
int T,n,k,a[maxn],sta[maxn],dp[maxn][259];
unsigned char temp[maxn];

vector<int>v[maxn];
inline void inc(register int &a,register int &b){
    a=a+b>=mod ? a+b-mod:a+b;
}

int main(){
	freopen("mul.in","r",stdin);
	freopen("mul.out","w",stdout);
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)v[i].clear(),sta[i]=0;
        for(int i=1;i<=n;i++){
            a[i]=i;
            for(int j=0;j<8;j++)
                if(a[i]%(p[j]*p[j])==0)sta[i]=-1;
                else if(a[i]%p[j]==0)a[i]/=p[j],sta[i]|=(1<<j);
        }
        for(int i=1;i<=n;i++)
            if(~sta[i]){
                if(a[i]==1)v[i].push_back(i);
                else v[a[i]].push_back(i);
            }
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=1;i<=n;i++)
            if(~sta[i]&&v[i].size()){
                register int sz=v[i].size();
                for(int j=0;j<sz;j++) temp[j]=sta[v[i][j]];
				for(register int j=k-1;j>=0;j--)
					for(register int l=0;l<sz;l++)
						for(register int v=temp[l],s=255^v;;s=(s-1)&(255^v)){
							if((s&temp[l])==0) inc(dp[j+1][s|v],dp[j][s]);
							if(!s) break;
						}
            }
        long long ans=0;
        for(int i=1;i<=k;i++)
            for(int j=0;j<256;j++)
                ans+=dp[i][j];
        cout<<ans%mod<<endl;
    }    
    return 0;
}
