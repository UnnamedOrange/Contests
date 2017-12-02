#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct BI{
	short num[500];
	BI(){
		memset(num,0,sizeof(num));
	}
	BI operator + (const BI &tar) const {
		BI ret;
		int ws=max(num[0],tar.num[0]);
		for(int i=1;i<=ws;i++){
			ret.num[i]+=num[i]+tar.num[i];
			if(ret.num[i]>=10){
				ret.num[i+1]++;
				ret.num[i]-=10;
			}
		}
		ret.num[0]=ws;
		if(ret.num[ws+1]) ret.num[0]++;
		return ret;
	}
	BI operator / (const int &tar) const {
		BI ret;
		for(int i=num[0],wait=0;i>=1;i--){
			wait=wait*10+num[i];
			if(wait<tar) continue;
			ret.num[i]=wait/tar;
			wait%=tar;
		}
		for(ret.num[0]=num[0];ret.num[0]>=1&&!ret.num[ret.num[0]];ret.num[0]--);
		return ret;
	}
};
short mod7 (BI tar) {
	short wait=0;
	for(int i=tar.num[0];i>=1;i--){
		wait=wait*10+tar.num[i];
		if(wait<7) continue;
		wait%=7;
	}
	return wait;
}
BI dp[2][2005];
short work(int n){
	int a=n+1,b=n<<1;//b>a
	for(int i=0;i<=b;i++){
		dp[0][0].num[0]=dp[0][0].num[1]=1;
		for(int j=1;j<i;j++){
			dp[0][j]=dp[1][j]+dp[1][j-1];
		}
		dp[0][i].num[0]=dp[0][i].num[1]=1;
		for(int j=0;j<=i;j++){
			dp[1][j]=dp[0][j];
		}
	}
	return mod7(dp[0][a]/n);
}
int main(){
	//freopen("stack.in","r",stdin);
	//freopen("stack.out","w",stdout);
	short n;
	scanf("%hd",&n);
	switch(n){
		case 0:
			printf("1");
			goto Ends;
		case 1:
			printf("1");
			goto Ends;
		case 2:
			printf("2");
			goto Ends;
		case 3:
			printf("5");
			goto Ends;
		default:printf("%hd",work(n));
	}
	Ends:
	//fclose(stdin),fclose(stdout);
	return 0;
}
