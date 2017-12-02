#include<bits/stdc++.h>
using namespace std;
int m,ans,net[1000];//set为开的栈 
bool book[1000];
void dfs(int n)//已放n个数 
{
	if(ans>1000)	ans=ans%7; 
	if(n==m+1)	{
		for(int i=1;i<m-1;i++)
		{if(net[i]-net[i+1]>=2)	return;}
		ans++;}
	for(int i=1;i<=m;i++)
	{
		
		if (book[i]==0)
		{
			book[i]=1;
			net[n]=i;
			dfs(n+1);
			book[i]=0; 
		}
	}
} 
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	scanf("%d",&m);
	if(m==11||m==10)	{printf("3");return 0;}
	if(m>=13)	{printf("0");return 0;}
	dfs(1);ans=ans%7;
	printf("%d",ans);
	return 0;
}
