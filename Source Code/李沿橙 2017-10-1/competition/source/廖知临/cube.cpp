#include<bits/stdc++.h>
using namespace std;
int p,num[10005]; 
char net;
struct	biao{//һǧ��ջ
	int a[10005];
	int k;//��k��Ԫ�� 
}use[10005];
inline int read()//�����Ż�
{
  	int num=0;
  	char c;
  	while(isspace(c=getchar()));
  	while(num=num*10+c-48,isdigit(c=getchar()));
  	return num;
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	scanf("%d",&p);
	for(int i=1;i<=1005;i++)
	{	num[i]=i;//ÿ��Ԫ��ָ�����ջ 
		use[i].a[1]=i;//��ײ��Ԫ��Ϊ�Լ� 
		use[i].k=1;
	}
	for(int i=1;i<=p;i++)
	{
		cin>>net;
		if(net=='M')//��x����ջ�ŵ�y��ջ���Ϸ� 
		{
			int x,y;
			x=read();y=read();
			for(int i=1;i<=use[num[x]].k;i++)	
				use[num[y]].a[++use[num[y]].k]=use[num[x]].a[i];	
			for(int i=1;i<=use[num[x]].k;i++)	 
				num[use[num[x]].a[i]]=num[y];//��Ԫ�ص�ջ�ĳ�y��ջ
		}
		else//��x�·������� 
		{
			int z;
			z=read();
			for(int i=1;i<=use[num[z]].k;i++)
				if(use[num[z]].a[i]==z)	printf("%d\n",i-1);
		}
	}
	return 0;
}
