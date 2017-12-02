#include<bits/stdc++.h>
using namespace std;
long long ans,sum;
int from,want,how;int h[10000010];bool z[10000100];
int g(int x,int y)//求最大公约数 
{
	if(y!=0)return g(y,x%y);
	else return x;	
}
void qu()//求快速幂 
{
	int k=how-1,key,first=sum;
	while(k>0)
	{
		key=sum/2;
		if(k%2)sum=(sum*first)%1000000000,k--;
		if(k==0)return;
		if(!k%2)sum=(key*sum)%1000000000+(sum-key)*sum%1000000000,k/=2;
		if(sum>=1000000000)sum-=1000000000;
	} 
}
void kkk(int n)//欧拉筛 
{
	int i,j,tot=0;
	for(i=2;i<=n;i++)
	{
		if(!z[i])h[++tot]=i;
		j=1;
		while(i*h[j]<=n&&i%h[j]&&j<=tot) z[i*h[j]]=true,j++;
		if(i*h[i]>n)return ;
		if(i%h[j]) z[i*h[j]]=true;
	}
} 
//998244353
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int i,times,tot,key=1;
	memset(z,0,sizeof(z));
	scanf("%d%d%d",&from,&want,&how);
	if(want<=10000000&&from<1000000)kkk(want);
	else if(from<1000000) kkk(10000000);
	for(times=from;times<=want;times++)
	{
		tot=0,sum=0;
		if(times<=1000000&&z[times])sum=((times*(times-1))%1000000000)/(times-1);
		else
		{
			sum+=times-1,tot++;
			if(times%2)//奇数 
			{
				for(i=times-2;i>2;i--)
					if(times%i&&g(times,i)==1)
					{
						sum+=i,tot++;//计算互质数的和以及个数 
					}
				sum+=2,tot++;	
			}
			else //偶数 
			{
				for(i=times-3;i>2;i-=2)
					if(times%i&&g(times,i)==1)
					{
						sum+=i,tot++;//计算互质数的和以及个数 
					}
			}	
			if(times!=2)sum++,tot++;
			sum*=2;
			sum/=tot;
		}
		if(how!=1)qu();
		ans+=sum;
		if(ans>=998244353)ans-=998244353;
	}
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
