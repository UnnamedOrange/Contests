#include<cstdio>
#include<cstring>
#define MAXN 100005 
using namespace std;
int dp1l[MAXN],dp0l[MAXN],dp0r[MAXN];
char s[MAXN];
inline void up_min(const int &a,int &b){
	if(a<b) b=a;
}
int main(){
	freopen("reverse.in","r",stdin),freopen("reverse.out","w",stdout);
	int len,sum0=0,sum1;
	scanf("%s",s+1);
	len=strlen(s+1);
	int ans=len;
	for(int i=1;i<=len;i++){
		switch(s[i]){
			case 49:
				dp1l[i]=dp1l[i-1]+1;
				dp0l[i]=dp0l[i-1];
				break;
			case 48:
				dp1l[i]=dp1l[i-1];
				dp0l[i]=dp0l[i-1]+1;
				sum0++;
		}
	}
	sum1=len-sum0;
	for(int i=0;i<=len;i++) dp0r[i]=sum0-dp0l[i];
	for(int i=0;i<=len&&ans;i++)
		up_min(dp1l[i]+dp0r[i],ans);
	printf("%d",ans);
	fclose(stdin),fclose(stdout);
	return 0;
}
