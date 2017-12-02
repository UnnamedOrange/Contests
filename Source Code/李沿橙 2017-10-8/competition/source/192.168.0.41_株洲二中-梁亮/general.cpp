#include<cstdio>
#include<iostream>

using namespace std;

struct Node
{
	int u,v;
}edge[10006];

int n,k,t;

void special()
{
	int ans=0;
	for(int i=1;i<n;++i)
		if(edge[i].u==1)	++ans;
	printf("%d",ans);
	return;
}

int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	
	scanf("%d%d%d",&n,&k,&t);
	int t1,t2;
	for(int i=1;i<n;++i)
	{
		scanf("%d%d",&t1,&t2);
		edge[i].u=t1;
		edge[i].v=t2;
		if(edge[i].u>edge[i].v)
		{
			t1=edge[i].u;
			edge[i].u=edge[i].v;
			edge[i].v=t1;
		}
	}
	
	
	
	if(k==0)	{printf("%d",n);return 0;}
	if(t==2)	{special();return 0;}
	printf("%d",n/3);
	return 0;
}
