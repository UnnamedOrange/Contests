#include<cstdio>
#include<iostream>

using namespace std;

struct Node
{
	int from,to;
}edge[10004];

int n,v[10004];
int sum[10004];
int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.in","w",stdout); 
	int order[10004];
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		sum[i]=1;
		
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&v[i]);
		sum[n]=sum[n]*v[i];
	}
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&edge[i].from,&edge[i].to);
	}
	for(int i=1;i<n;++i)
		scanf("%d",&order[n-i]);
	for(int i=1;i<n;++i)
	{
		v[edge[order[i]].from]+=v[edge[order[i]].to];
		v[edge[order[i]].to]=1;
		for(int j=1;j<=n;++j)
			sum[n-i]*=v[j];
	}
	for(int i=1;i<=n;++i)
		printf("%d\n",sum[i]);
	return 0;
}

//我们可以有梦想！ 
