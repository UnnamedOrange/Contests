#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<queue>
#include<map>
#include<bitset>
#include<stack>
#include<vector>
#include<set>
using namespace std;
#define MAXN 100010
#define MAXM 1010
#define INF 1000000000
#define MOD 1000000007
#define ll long long
#define eps 1e-8
char s[MAXN];
char b[MAXN]="!erewrwerwer";
int nxt[MAXN];
int trans[MAXN][128];
int f[MAXN][20];
int n;
int ans;
int main(){
	freopen("erewrwerwer10.in","r",stdin);
	freopen("erewrwerwer10.out","w",stdout);
	int i,j,k;
	scanf("%s",s+1);
	n=strlen(s+1);
	f[0][0]=1;
	for(i=1;i<=n;i++){
		f[i][0]=1;
		for(j=1;j<=11;j++){
			if(s[i]==b[j]){
				f[i][j]=(f[i-1][j-1]+f[i-1][j])%MOD;
			}else{
				f[i][j]=f[i-1][j];
			}
		}
	}
	printf("%d\n",f[n][11]);
	return 0;
}

/*
erewrwerwe?rewrwerwer
*/
