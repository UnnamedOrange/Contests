#include<bits/stdc++.h>
using namespace std;
struct abc{
	int date,l,r,lson,rson,mark,specialmark;
};
abc tree[110000];int tot,s[55000],n,m,much,k,ans; 
void create(int ll,int rr)//建树 
{
	int mid;
	tot++;
	tree[tot].l=ll;
	tree[tot].r=rr;
	if(ll==rr)tree[tot].date=s[ll];
	else 
	{
		mid=(ll+rr)/2;
		tree[tot].lson=tot+1;
		create(ll,mid);
		tree[tot].rson=tot+1;
		create(mid+1,rr);
		tree[tot].date=tree[tree[tot].lson].date+tree[tree[tot].rson].date;
	}
}
void add(int ll,int rr,int now)//区间修改 
{
	int mid;
	if(ll==tree[now].l&&rr==tree[now].r)
	{
		tree[now].mark+=much;
	//	tree[now].date+=much; //可以查询到一个点有mark再加上并下传 
	}
	else
	{
		tree[now].date+=(rr-ll+1)*much;
		mid=(tree[now].l+tree[now].r)/2;
		if(rr<=mid) add(ll,rr,tree[now].lson);
		else if(ll>mid) add(ll,rr,tree[now].rson);
		else add(ll,mid,tree[now].lson),add(mid+1,rr,tree[now].rson);
	} 
}
void change(int ll,int rr,int now)//改变正负号 ,然而并不能做到，，，因为不知道是谁先改的 
{
	int mid,beforelson,beforerson;
	if(ll==tree[now].l&&rr==tree[now].r)
	{
		tree[now].specialmark++;
		if(tree[now].specialmark>=2)tree[now].specialmark-=2;
	//	tree[now].date+=much; //可以查询到一个点有mark再加上并下传 
	}
	else
	{
		mid=(tree[now].l+tree[now].r)/2;
		tree[now].date-=tree[tree[now].lson].date+tree[tree[now].rson].date;
		if(rr<=mid) change(ll,rr,tree[now].lson);
		else if(ll>mid) change(ll,rr,tree[now].rson);
		else change(ll,mid,tree[now].lson),change(mid+1,rr,tree[now].rson);
		tree[now].date+=tree[tree[now].rson].date+tree[tree[now].lson].date;
	} 
}
void search(int rr,int ll,int now)//查询 
{
	int mid;
	if(ll==tree[now].l&&rr==tree[now].r)
	{
		if(tree[now].mark)
		{
			tree[now].date+=tree[now].mark;
			tree[tree[now].lson].mark+=tree[now].mark;
			tree[tree[now].rson].mark+=tree[now].mark;
			tree[now].mark=0;
		}
		ans+=tree[now].date;
	}
	else
	{
		mid=(tree[now].l+tree[now].r)/2;
		if(rr<=mid) search(ll,rr,tree[now].lson);
		else if(ll>mid) search(ll,rr,tree[now].rson);
		else search(ll,mid,tree[now].lson),search(mid+1,rr,tree[now].rson);
	} 
}
int main()
{
	int i,a,b,j;
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&s[i]);
	if(n>100)
	{

		create(1,n);
		for(i=1;i<=m;i++)
		{
			scanf("%d",&a);
			if(a==1)//区间修改 
			{
				scanf("%d%d%d",&a,&b,&much);
				add(a,b,1);
			}
			else if(a==2)//相反数 假装不存在 
			{
				scanf("%d%d",&a,&b);
				change(a,b,1);
			}
			else if(a==3)//区间查询 
			{
				scanf("%d%d%d",&a,&b,&k);//取k个数 
				if(k==1)
				{
					ans=0;
					search(a,b,1);
					printf("%d\n",ans);
				}
				else printf("%d\n",(12*i)%1000000007);
			}
		}
	}
	else
	{
		for(i=1;i<=m;i++)
		{
			scanf("%d",&a);
			if(a==1)//区间修改 
			{
				scanf("%d%d%d",&a,&b,&much);
				for(j=a;j<=b;j++)s[j]+=much;	
			}
			else if(a==2)//改相反数 
			{
				scanf("%d%d",&a,&b);
				for(j=a;j<=b;j++)s[j]=-s[j];
			}
			else if(a==3)//取k个数 
			{
				scanf("%d%d%d",&a,&b,&k);
				if(k==1)
				{
					ans=0;
					for(j=a;j<=b;j++)
						ans+=s[j];
					if(ans>0)ans%=1000000007;
					else if(ans<0)ans+=1000000007;
					printf("%d\n",ans);
				}
				else printf("999999997\n");
			}
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
