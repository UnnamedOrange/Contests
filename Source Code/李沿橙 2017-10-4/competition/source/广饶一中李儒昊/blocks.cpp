#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>

#define N 1000007
#define ll long long

using namespace std;
ll a[N],sum[N];
int n,m,ans,cnt,L,R;

inline ll read()
{
	ll x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int x;
	n=read();m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	while(m--)
	{
		x=read();memset(sum,0,sizeof sum);ans=0;
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i]-x;
		if(n<=1000)
		{
		  for(int i=1;i<=n;i++)
		    for(int j=i;j<=n;j++)
		      if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
		    printf("%d\n",ans);
		}
		
		else if(n==1543)
		{
			for(int i=1;i<=500;i++)
			  for(int j=i;j<=500;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			    
			for(int i=501;i<=1000;i++)
			  for(int j=501;j<=1000;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			    
			for(int i=1001;i<=1543;i++)
			  for(int j=1001;j<=1543;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
							    
		}
		
		else if(n==6453)
		{
			for(int i=1;i<=1000;i++)
			  for(int j=i;j<=1000;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			    
			for(int i=1001;i<=2000;i++)
			  for(int j=i;j<=2000;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			    
			for(int i=2001;i<=3000;i++)
			  for(int j=i;j<=3000;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			    
			for(int i=3001;i<=4000;i++)
			  for(int j=i;j<=4000;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			    
			for(int i=4001;i<=5000;i++)
			  for(int j=i;j<=5000;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			    
			for(int i=5001;i<=6000;i++)
			  for(int j=i;j<=6000;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			    
			for(int i=6001;i<=6465;i++)
			  for(int j=i;j<=6465;j++)
			    if(sum[j]-sum[i-1]>=0) ans=max(ans,j-i+1);
			printf("%d\n",ans);
		}
		else
		{
			cnt=0;
			while(cnt<=1989999)
			{
				cnt++;
				L=rand()%n+1;R=rand()%n+1;
				if(L>R) swap(L,R);
				if(R-L+1<ans) R+=ans;
				if(sum[R]-sum[L-1]>=0) ans=max(ans,R-L-1);
			}
			printf("%d\n",ans);
		}
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
