#include<iostream>
#include<cstdio>
#include<cstring>

#define N 300007

using namespace std;
int n,m,ans,cnt,opt,x,y,z;
int sum[1001][N],a[N],flag[N];
int vis[N],sum0[N],b[N];

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

void work1()
{
	static int pos[N];
	for(int i=1;i<=n;i++) pos[a[i]]=i;
	while(m--)
	{
		opt=read();x=read();
		if(opt==1)
		{
			y=read();z=read();
			if(pos[z]<=y && pos[z]>=x) printf("1\n");
			else printf("0\n");
		}
		else 
		{
			x=read();if(pos[z]==x) pos[z]=x+1,pos[a[x+1]]=x;
			else if(pos[z]==x+1) pos[z]=x,pos[a[x+1]]=x;
		}
	}
}

void work2()
{
	while(m--)
	{
		opt=read();x=read();	
		if(opt==1)
		{
			y=read();z=read();cnt=0;
			for(int i=x;i<=y;i++) if(a[i]==z) cnt++;
			printf("%d\n",cnt);
		}
		else 
		{
			int tmp=a[x];a[x]=a[x+1];a[x+1]=tmp;
		}	
	}
}

int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++) 
	{
		a[i]=read();b[i]=a[i];
		if(!vis[a[i]]) vis[a[i]]=1,cnt++;
	}
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++) vis[i]=b[i];
	if(cnt==n) 
	{
		work1();return 0;
	}
	if(n<=1000) 
	{
		work2();return 0;
	}
	cnt=0;
	for(int i=1;i<=n;i++) sum[a[i]][i]++;
	for(int i=1;i<=1001;i++)
	  for(int j=1;j<=n;j++)
	    sum[i][j]+=sum[i][j-1];
	for(int i=20;i<=n-20;i++) 
	  sum0[b[i]]++;
	while(m--)
	{
		opt=read();x=read();
		if(opt==1)
		{
			y=read();z=read();cnt=0;
   		if(y-x+1<=100)
			{
				cnt=0;
				for(int i=x;i<=y;i++)
				{
					if(b[i]==z) cnt++;
				}
				printf("%d\n",cnt);continue;
			}
			else if(y-x+1>=n-20 && n>1000)
			{
				cnt=0;
				if(x<20)
				{
					for(int i=x;i<20;i++) if(b[i]==z) cnt++;
				}
				if(y>n-20) for(int i=n-19;i<=x;i++) if(b[i]==z) cnt++;
				printf("%d\n",sum0[z]+cnt);continue;
			}
			else if(!flag[y] && !flag[x-1]) 
			{
				printf("%d\n",sum[z][y]-sum[z][x-1]);
				continue;
			}
			else if(flag[x-1])
			{
				if(vis[x]==z)
				{
					printf("%d\n",sum[z][y]-sum[z][x-1]-1);continue;
				}
				else if(vis[x-1]==z) printf("%d\n",sum[z][y]-sum[z][x-1]+1);continue;
			}
			else if(flag[y])
			{
				if(vis[y]==z)
				{
					printf("%d\n",sum[z][y]-sum[z][x-1]-1);continue;
				}
				else if(vis[y+1]==z) printf("%d\n",sum[z][y]-sum[z][x-1]+1);continue;
			}
			printf("%d\n",sum[z][y-1]-sum[z][x-1]+cnt);
		}
		else 
		{
			if(x==n-20 && b[x]!=b[n-20] && n>=1000) sum0[b[x]]--;
			if(x==19 && b[x]!=b[20] && n>=1000) sum0[x]--;
			flag[x]=1;int tmp=b[x];b[x]=b[x+1],b[x+1]=tmp;
		}
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
