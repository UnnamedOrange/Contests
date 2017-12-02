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
inline int read(){
    int X=0,w=1; char ch=0;
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
string s;
int dp[100001][2];
int main(){
    freopen("reverse.in","r",stdin);
    freopen("reverse.out","w",stdout);
    getline(cin,s);
    int l=s.length();
    for(int i=0;i<l-1;i++){
    	if(s[i]=='0'){
    		dp[i][0]=dp[i-1][0];
    		dp[i][1]=min(dp[i-1][0]+1,dp[i-1][1]+1);
		}	
		else{
			dp[i][0]=dp[i-1][0]+1;
			dp[i][1]=min(dp[i-1][1],dp[i-1][0]);
		}
	}
	if(s[s.length()-1]=='1') printf("%d",min(dp[l-2][0],dp[l-2][1]));
	else printf("%d",min(dp[l-2][0],dp[l-2][1]+1));
    return 0;
}
