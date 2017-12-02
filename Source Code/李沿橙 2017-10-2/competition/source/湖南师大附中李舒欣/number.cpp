#include<bits/stdc++.h>
using namespace std;
int n,ans,tem[10000];
signed main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%d",&n);
	if(n<=10)
	{
		cout<<0<<endl;
		return 0;
	}
	if(n>10)
	{
		for(int i=11;i<=min(99,n);i++)
		{
			int x=i%10;
			int y=i/10;
			int tem1=ans;
			if((x*10+y)<i&&x!=0)ans++;
			if(x==y)ans++;
		}
		if(n<100)
		{
			cout<<ans<<endl;
			return 0;
		}
	}
	if(n>=100)
	{
		for(int i=100;i<=min(n,999);i++)
		{
			int x=i/10;
			int y=(i/10)%10;
			int z=i%10;
			x/=10;
			tem[1]=y*100+x*10+z;
			tem[2]=z*100+x*10+y;
			tem[3]=x*100+z*10+y;
			tem[4]=y*100+z*10+x;
			tem[5]=z*100+y*10+x;
			for(int j=1;j<=5;j++)if(tem[j]<i&&tem[j]>=100)ans++;
			if(x==y&&y==z)ans+=2;
			else if(x==y||y==z||z==x)ans+=2;
		}
		if(n<1000)cout<<ans<<endl;
	}
	if(n>=1000)
	{
		for(int i=1000;i<=n;i++)
		{
			int x=i/1000;
			int y=(i/100)%10;
			int z=(i/10)%10;
			int k=i%10;
			tem[1]=x*1000+y*100+k*10+z;
			tem[2]=x*1000+k*100+y*10+z;
			tem[3]=x*1000+k*100+z*10+y;
			tem[4]=x*1000+z*100+y*10+k;
			tem[22]=x*1000+z*100+k*10+y;
			tem[5]=y*1000+x*100+z*10+k;
			tem[6]=y*1000+x*100+k*10+z;
			tem[7]=y*1000+k*100+x*10+z;
			tem[8]=y*1000+k*100+z*10+x;
			tem[9]=y*1000+z*100+x*10+k;
			tem[23]=y*1000+z*100+k*10+x;
			tem[10]=z*1000+y*100+x*10+k;
			tem[11]=z*1000+y*100+k*10+x;
			tem[12]=z*1000+k*100+y*10+x;
			tem[13]=z*1000+k*100+x*10+y;
			tem[14]=z*1000+x*100+k*10+y;
			tem[15]=z*1000+x*100+y*10+k;
			tem[16]=k*1000+x*100+y*10+z;
			tem[17]=k*1000+x*100+z*10+y;
			tem[18]=k*1000+y*100+x*10+z;
			tem[19]=k*1000+y*100+z*10+x;
			tem[20]=k*1000+z*100+y*10+x;
			tem[21]=k*1000+z*100+x*10+y;
			for(int j=1;j<=23;j++)if(tem[j]<i&&tem[j]>=1000)ans++;
			if(k==x&&x==y&&y==z)ans+=3;
			else if((k==x&&x==y)||(k==x&&x==z)||(x==y&&y==z))ans+=8;
			else if((k==x)||(k==y)||(k==z)||(z==x)||(x==y)||(y==z))ans+=6;
		}
		cout<<ans<<endl;
	}
}
