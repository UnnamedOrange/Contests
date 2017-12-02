#include<cstdio>
#include<iostream>

using namespace std;

int n,a[304];
int gcd[1004][1004];
int win[6]={0};
bool found[1004][1004];
bool book[304];

void input()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
	}
	return ;
}

int foundgcd(int x,int y)
{
	if(x>y)	return foundgcd(y,x);
	if(x==0)	return y;
	return foundgcd(x,y%x);
}

void dfs(int board,int step,int rest)//step : 0 xiuxiu 1 huahua
{
	if(rest==0)
	{
		++win[1-step];
		return;
	}
	if(board==1)
	{
		++win[step];
		return;
	}
	for(int i=1;i<=n;++i)
	{
		if(book[i]==false)
		{
			book[i]=true;
			
			if(found[board][i]==false)
			{
				found[board][i]=true;
				gcd[board][i]=gcd[i][board]=foundgcd(board,i);
			}
			
			dfs(gcd[board][i],1-step,rest-1);
			
			
			book[i]=false;
			
		}
	}
	return ;
}

int main()
{
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	input();

	
	for(int i=1;i<=n;++i)
	{
		book[i]=true;
		dfs(i,1,n-1);
		book[i]=false;
	}
	
	double ans;
	ans=(double)win[0]/(win[0]+win[1]);
	printf("%.9llf",ans);
	
	printf(" 1.000000000");
	return 0;
}

//我们可以带着梦想打暴力！ 
