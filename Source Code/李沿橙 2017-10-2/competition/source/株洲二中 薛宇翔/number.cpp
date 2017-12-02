#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n;
long long ans=0;
int ax[2][2][2][2][2][2][2][2][2][2];
int main()
{	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)
	{
		int x=i;bool xc[10];
		memset(xc,0,sizeof(xc));
		while(x){
			xc[x%10]=true;
			x/=10;
		}
		ans+=ax[xc[0]][xc[1]][xc[2]][xc[3]][xc[4]]
		[xc[5]][xc[6]][xc[7]][xc[8]][xc[9]]++;
	}
	cout<<ans<<endl;
	return 0;
}
