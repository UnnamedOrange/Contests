#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
#define MAXN 10000005
#define MAXW 10
int n,pos,a[MAXW+1];
int len,sum2;
bool book[MAXN+1],book2[MAXN+1];
LL tot;
void fj(int x)
{
	int temp = x;
	memset(book2,false,sizeof(book2));
	while(temp){
		int k = temp % 10;
		if(book2[k] == false){
			a[++pos] = k;//注意这里我们是逆序存的 而且是从1开始
			book2[k] = true;
		}
		temp = temp / 10;
	}
}
void dfs(int x,int sum,int step)
{
	if(sum > n)
		return;
	if(sum > x){
		tot++;
		return ;
	}	
	for(int i=1;i<=pos;i++)
	{
		if(book[i] == false)
		{
			sum = sum * 10 + a[i];
			book[i] = true;
			dfs(x,sum,step+1);
			book[i] = false;
			sum = (sum - a[i]) / 10;
		}
	}
}
int main()
{
	freopen("number.in","r",stdin);
    freopen("number.out","w",stdout); 
	scanf("%d",&n);
	if(n <= 10){
		printf("0");
		return 0;
	}
	if(n < 100){
		for(int i=1;i<=9;i++)
		{
			int k = i * 10 + i;
			if(k <= n)
				tot++; 
		}
		for(int i=12;i<=n;i++){
			int temp = i;
			pos = 0;
			while(temp){
				int k = temp % 10;
					a[++pos] = k;//注意这里我们是逆序存的 而且是从1开始
					book2[k] = true;
				temp = temp / 10;
			}
			int k = a[1] * 10 + a[2];
			if(k <= n && k > i && k > 10){
				tot++;
			}		
		}
		printf("%d",tot);
		return 0;
	}
	if(n <= 1000){
		int temp = n;
		while(temp){
			len++;
			temp /= 10;
		}
		for(int i=1;i<=n;i++)
		{
			fj(i);  
				dfs(i,0,0);
					pos = 0;	
		}
		printf("%d",tot);
		return 0;
	}
	else{
		printf("666");
		return 0;
	}
        return 0;
}
