#include<cmath>
#include<cstdio>
using namespace std;
int n,y=1,p,x[10],use[10],cmp,ans[10000005],k=1,fin,u,shu;
void dfs(int z,int num,int zho)//��yλ����zλ��ǰ��ֵΪnum�Ѿ��õ����� 
{
	if(z>=y)	return;
	for(int i=0;i<=9;i++)
	{
		if(x[i])
		{
			if(use[i])
				{use[i]=0;zho++;}
			u=(num*pow(10,z)+i);
			if(u>cmp&&u<=n)	//�жϴ�С 
			{
				if(zho>=shu)//�ж��Ƿ�������ô������ 
					ans[k++]=u;
				dfs(z+1,u,zho);
			}
			else return;
		}
	}	
}
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%d",&n);
	p=n;
	while(p/10>0)
		{p=p/10;y++;}	
	for(cmp=1;cmp<=n;cmp++)
	{
		x[cmp%10]=1;use[cmp%10]=1;shu++;p=cmp;
		while(p/10>0)
		{p=p/10;x[p%10]=1;if(use[p%10]!=1)	{use[p%10]=1;shu++;}}
		for(int i=1;i<=9;i++)
		{
		if(x[i])
			dfs(1,i,1);
		}
		for(int i=0;i<=9;i++)	{x[i]=0;use[i]=0;}
		shu=0;
	}
	printf("%d",k-1);
}
