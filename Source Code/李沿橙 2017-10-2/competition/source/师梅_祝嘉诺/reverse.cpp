#include<bits/stdc++.h> //100110011000011000100
using namespace std;
int len,dp[200000];
char a[200000];
bool book[200000];
int search(int now)
{
	if(book[now]) return dp[now];
	if(now==len-1)
	{
		book[now]=true;
		dp[now]=0;
		return dp[now];
	}
	int zero=0;
	for(int i=now;i<len;i++)//ÕÒÁã 
	{
		if(a[i]=='0') zero++;
	}
	if(zero==0) return 0;
	if(a[now]=='0')
	{
		book[now]=true;
		dp[now]=search(now+1);
		return dp[now];
	}
	if(a[now]=='1')
	{
		book[now]==true;
		dp[now]=min(zero,search(now+1)+1);
		return dp[now];
	}		
}

int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	ios::sync_with_stdio(false);
	gets(a);
	len=strlen(a);
	cout<<search(0);
	//fclose(stdin);fclose(stdout);
	return 0;
}
