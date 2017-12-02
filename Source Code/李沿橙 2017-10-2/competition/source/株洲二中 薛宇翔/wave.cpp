#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,k;
int ax[2000005];
int ans[2000005][3];
int main()
{	freopen("wave.in","r",stdin);
	freopen("wave.out"."w",stdout);
	n=read();
	k=read();
	for(int i=1;i<=n;i++)ax[i]=read();
	ans[1][0]=1;
	for(int i=2;i<=n;i++){
		for(int j=i-1;j>=1;j--){
			if(ans[j][0]%2){
				if(ax[i]>=ax[j]){
				if(ans[j][0]+1>=ans[i][0])
				{
				ans[i][0]=ans[j][0]+1;
				ans[i][1]=ax[j];}
				break;
				}
				else ans[i][0]=1;
			}
			if(ans[j][0]%2==0){
				if(ax[i]<=ax[j]&&
				abs(ax[i]-ans[j][1])>=k){
				ans[i][0]=max(ans[i][0],ans[j][0]+1);
				break;
				}
				else ans[i][0]=1;
			}
			
		}
	}
	int out=0;
	for(int i=1;i<=n;i++)if(ans[i][0]%2)out=max(out,ans[i][0]);
	cout<<out;
	return 0;
}
