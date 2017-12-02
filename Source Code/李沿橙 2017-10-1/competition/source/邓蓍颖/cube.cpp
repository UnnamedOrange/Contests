#include<bits/stdc++.h>
using namespace std;
int son[30010],father[30010];int n/*存下每个数的下面那个数是什么*/;
int findson(int x)//找最底下的 
{
	while(x!=son[x])x=son[x];
	return x;
}
int findfather(int x)//找最上面的 
{
	while(x!=father[x])x=father[x];
	return x;
}
int findans(int x)
{
	int ans=0;
	while(x!=son[x])
		x=son[x],ans++;
	return ans;
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int i,x,y,k,t;char ch;
	scanf("%d",&n);
	for(i=1;i<=30000;i++)son[i]=i,father[i]=i;
	for(i=1;i<=n;i++)
	{
		cin>>ch;
		if(ch=='M')
		{
			scanf("%d%d",&x,&y);
			k=findson(x);
			t=findfather(y);
			son[k]=t;
			father[t]=k;//接起来（首尾） 
		}
		else  
		{
			scanf("%d",&x);
			x=findans(x);
			printf("%d\n",x);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
