#include<bits/stdc++.h>
using namespace std;
int n,a,ned[26],num[26],use[26],x;
inline int read()//�����Ż�
{
  	int num=0;
  	char c;
  	while(isspace(c=getchar()));
  	while(num=num*10+c-48,isdigit(c=getchar()));
  	return num;
}
int cashier()
{
		int sum=0;
		for(int i=0;i<=23;i++)
			{ned[i]=read();}//��i��СʱҪa���� 
		for(int i=0;i<=23;i++)
		{
			a=read();
			num[i]=a;//��i��Сʱ��a����
			if(a==0)	continue;
			x=i;
			for(int k=1;k<=8;k++)
			{
				use[x++]+=a;//�����Ժ�Ҫ���� 
				if(x==24)	x=0;
			}
		}
		for(int i=0;i<=23;i++)
			if(use[i]<ned[i])	{printf("-1\n");return 0;}
		for(int i=0;i<=23;i++)
		{
			a=num[i];	
			x=i;
			int nu=2147483647;//��ѯ��ɾ������ 
			for(int k=1;k<=8;k++) 
			{
				if(use[x]-ned[x]<nu)		nu=use[x]-ned[x];
				x++;
				if(x==24)	x=0;
			}
			if(nu>num[i])	nu=num[i];
			if(nu==0)	continue;
			x=i;
			for(int k=1;k<=8;k++)
			{
				use[x++]-=nu;
				if(x==24)	x=0;
			}
			num[i]-=nu;
		}	
		for(int i=0;i<=23;i++)
			sum+=num[i];	
		printf("%d\n",sum);
		memset(use,0,sizeof(use));
		return 0;
}
int main()
{
	freopen("cashier.in","r",stdout);
	freopen("cashier.out","w",stdout);
	n=read();
	for(int z=1;z<=n;z++)//n������ 
		cashier();
	return 0;
}
