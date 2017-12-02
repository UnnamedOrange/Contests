# pragma G++ optimize "O2"
# pragma GCC optimize "O2"
#include<bits/stdc++.h>
using namespace std;
int a[50005],ned,all,use[50005],n,m,x,l,r,c;
long long ans;
inline int read()//¶ÁÈëÓÅ»¯
{
  	int num=0;
  	char c;
  	while(isspace(c=getchar()));
  	while(num=num*10+c-48,isdigit(c=getchar()));
  	return num;
}
void dfs(int x,int num,long long sum)
{
	if (ned+1==x) 
		{ans+=sum;if(ans>1000000007)	ans=ans%1000000007;
		return;}
	for (int i=num;i<=all;i++) 
		dfs(x+1,i+1,sum*use[i]);
}
int main()
{
	freopen("game.in","r",stdout);
	freopen("game.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=m;i++)
	{
		x=read();
		if(x==1)
		{
			l=read();r=read();scanf("%d",&c);
			for(int i=l;i<=r;i++)
				a[i]=a[i]+c;
		}
		if(x==2)
		{
			l=read();r=read();
			for(int i=l;i<=r;i++)
				a[i]=0-a[i];
		}
		if(x==3)
		{
			l=read();r=read();ned=read();all=r-l+1; 
			for(int i=1;i<=all;i++)
				use[i]=a[l++];
			sort(use+1,use+1+all);
			dfs(1,1,1); 
			if(ans<0)	ans+=1000000007;
			printf("%lld\n",ans);
			ans=0;
		}
	}
	return 0;
}
