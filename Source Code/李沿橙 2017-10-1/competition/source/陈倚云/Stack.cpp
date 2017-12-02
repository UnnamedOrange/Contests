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
inline int read(){
    int X=0,w=1; char ch=0;
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
using namespace std;
long long dp[500][500];
int main(){
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	int n=read();
	dp[1][0]=1;
	dp[1][1]=1;
	dp[2][0]=1;
	dp[2][1]=2;
	dp[2][2]=1;
	for(int i=3;i<=2*n+1;i++){
		dp[i][0]=1;
		for(int j=1;j<=i;j++) dp[i][j]=(dp[i-1][j]+dp[i-1][j-1]);
	}
	printf("%d",((dp[2*n][n])/(n+1))%7);
	
	return 0;	
}

