#include<bits/stdc++.h>
using namespace std;
struct abc{
	int tot,date;
};
int n,m,s[1000000],ans,k,all;abc p,maxn;//tot来统计长度，ans记录最大长度，maxn记录当前的值,
/*在理解一的情况下：论如何应对多余了放不下的情况：看多出来的值能不能除尽tot，若可以，就说明可以每次都一次性每个＋1，
一直到加完为止，不然就看长度有没有达到n，如果没有达到n，那么也可以放到其他的格子里，如果达到了n，
又除不尽tot，就必须拿一个格子出来存放多余的东西*/
/*理解二：直接贪*/
/*用最大区间和来做，用2个变量来记录最大和以及目前累加，
如果相加没有小于它应有的值就加入，否则就重新计数(或许这个贪心是错的？)*/
int read()
{
	char c;
	c=getchar();
	while(c>'9'||c<'0')c=getchar();
	return c-'0'; 
}
void kkk()
{
	int i,j;abc o;
	maxn.date=0,ans=0,maxn.tot=0,p.date=0,p.tot=0;
	for(i=1;i<=n;i++)
	{
		p.date+=s[i];
		p.tot++;
		if(p.date+maxn.date>=(maxn.tot+p.tot)*k)
		{
			maxn.date+=p.date;
			maxn.tot+=p.tot;
			p.tot=0,p.date=0;
		} 
		else
		{
			j=i+1;
			o.date=0,o.tot=0;
			while(j<=n&&s[j]+o.date>=(o.tot+1)*k)
			{
				o.date+=s[j],o.tot++;
				j++;
			}
			if((o.date-o.tot*k)+(maxn.date-maxn.tot*k)+s[i]>=k)
			{
				maxn.date+=o.date+s[i],maxn.tot+=o.tot+1;
				i=j;
			}
			else
			{
				if(maxn.tot>ans)ans=maxn.tot;
				maxn.tot=0;
				maxn.date=0;
				p.tot=0;
				p.date=0;
			}
		}
	}
	if(maxn.tot>ans)ans=maxn.tot;
	printf("%d ",ans);
}
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&s[i]);
	for(i=1;i<=m;i++)
	{
		scanf("%d",&k);
		kkk();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
