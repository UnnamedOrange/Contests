#include<bits/stdc++.h>
using namespace std;
int p,num[10005]; 
char net;
struct	biao{//一千个栈
	int a[10005];
	int k;//共k个元素 
}use[10005];
inline int read()//读入优化
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
	{	num[i]=i;//每个元素指向其的栈 
		use[i].a[1]=i;//最底层的元素为自己 
		use[i].k=1;
	}
	for(int i=1;i<=p;i++)
	{
		cin>>net;
		if(net=='M')//将x所在栈放到y的栈的上方 
		{
			int x,y;
			x=read();y=read();
			for(int i=1;i<=use[num[x]].k;i++)	
				use[num[y]].a[++use[num[y]].k]=use[num[x]].a[i];	
			for(int i=1;i<=use[num[x]].k;i++)	 
				num[use[num[x]].a[i]]=num[y];//将元素的栈改成y的栈
		}
		else//求x下方的数量 
		{
			int z;
			z=read();
			for(int i=1;i<=use[num[z]].k;i++)
				if(use[num[z]].a[i]==z)	printf("%d\n",i-1);
		}
	}
	return 0;
}
