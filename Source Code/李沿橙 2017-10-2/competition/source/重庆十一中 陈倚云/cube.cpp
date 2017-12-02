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
int n;
int ans;
string t1="0000000000",t2="0000000000";
int main(){
    freopen("cube.in","r",stdin);
    freopen("cube.out","w",stdout);
    n=read();
    for(int i=1;i<=n-1;i++){
    	for(int j=i+1;j<=n;j++){
    	     t1="0000000000",t2="0000000000";
    		int a=i,b=j;
    		while(a>0){
    			int s=a%10;
    			if(t1[s]=='0') t1[s]='1';
    			a=a/10;
			}
			while(b>0){
				int s=b%10;
				if(t2[s]=='0') t2[s]='1';
				b=b/10;
			}
			if(t1==t2)	ans++;
		}
	}
	printf("%d",ans);
    return 0;
}
