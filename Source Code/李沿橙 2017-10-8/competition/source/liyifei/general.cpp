#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
vector<int>s[101010];
int heap[101010],fa[101010],dep[101010],son[101010],vis[101010],num;
void insert_set(int x,int n)
{
	heap[n]=x;
	int t=n;
	while(t>1&&dep[heap[t]]>dep[heap[t/2]])
	{
		swap(heap[t],heap[t/2]);
		t=t/2;
	}
}
void delete_set(int n)
{
	int t,p;
	swap(heap[1],heap[n]);
	heap[n]=0;
	t=1;
	while(2*t<n)
	{
		if(2*t+1==n)
			p=2*t;
		else if(dep[heap[2*t]]>dep[heap[2*t+1]])
			p=2*t;
		else
			p=2*t+1;
		if(dep[heap[p]]>dep[heap[t]])
		{
			swap(heap[t],heap[p]);
			t=p;
		}
		else
			break;
	}
}
void dfs(int x)
{
	int y,i,c;
	c=s[x].size();
	son[x]=c-1;
	if(x==1)
		son[x]++;
	if(x!=1&&c==1)
	{
		num++;
		insert_set(x,num);
	}
	for(i=0;i<c;i++)
	{
		y=s[x][i];
		if(fa[x]==y)
			continue;
		fa[y]=x;
		dep[y]=dep[x]+1;
		dfs(y);
	}
	
}
int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	int n,m,k,ans,x,y,t,tmp,sum,i;
	scanf("%d%d%d",&n,&k,&m);
	for(i=1;i<=n;i++)
		vis[i]=10000;
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		s[x].push_back(y);
		s[y].push_back(x);
	}
	dfs(1);
	ans=0;
	while(num>0)
	{
		x=heap[1];
		//printf("%d ",x);
		sum=0;
		tmp=0;
		for(i=1;i<=k;i++)
		{
			if(x==1)
				break;
			x=fa[x];
			sum++;
			if(vis[x]+sum<=k)
			{
				tmp=1;
				break;
			}
		}
		if(tmp==0)
		{
			ans++;
			t=x;
			for(i=1;i<=k;i++)
			{
				vis[t]=min(vis[t],i-1);
				if(t==1)
					break;
				t=fa[t];					
			}
			if(vis[t]==10000)
			{
				son[fa[t]]--;
				if(son[fa[t]]==0)
				{
					num++;
					insert_set(fa[t],num);
				}
			}
			vis[t]=min(vis[t],k);
		}
		delete_set(num);
		num--;
	}
	printf("%d",ans);
 	return 0;
}

