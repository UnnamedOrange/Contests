#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
long long ans=0;
int tmp[20];
using namespace std;

int cnt=0;
void dfs(int numi,int now,int x)
{
	if(now==x)
	{
		ans++;
		for(int i=1;i<=cnt;i++) cout<<tmp[i]<<" ";
		cout<<endl;
		return ;
	}
	if(numi>0)
	{
		cnt++;
		tmp[cnt]=1;
		dfs(numi-1,now,x);
		cnt--;
	}
	cnt++;
	tmp[cnt]=2;
	dfs(numi+1,now+1,x);
	cnt--;
}

void work(int x)
{
	dfs(0,0,x);
}

int main()
{
	freopen("stack.in","r",stdin);
	//freopen("stack.ans","w",stdout);
	for(int n=1;n<=5;n++)
	{
		ans=0;
		work(n);
		printf("%lld\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
