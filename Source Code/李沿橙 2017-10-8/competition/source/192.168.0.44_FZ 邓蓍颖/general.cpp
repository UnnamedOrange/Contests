#include<bits/stdc++.h>
using namespace std;
struct abc{
	int date,next;
};
struct ab{
	int num,t,date;
};
int tot,n,k,special,have,w[100100];bool point[100100];abc h[200100];ab head[101000];
void add(int from,int want)
{
	tot++;
	h[tot].date=want;
	h[tot].next=head[from].date;
	head[from].date=tot;
	head[from].t++;
}
bool cmp(ab x,ab y)
{
	return x.t>y.t;	
} 
void kill(int where,int times)
{
	int want=head[where].date;
	if(!point[head[where].num])point[head[where].num]=true,have--;
	while(h[want].date)
	{
		if(!point[h[want].date])point[h[want].date]=true,have--;
		want=h[want].next;
		if(times>1)kill(w[h[want].date],times-1);
	}
}
int main()
{
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	int i,a,b;
	memset(point,0,sizeof(point));
	scanf("%d%d%d",&n,&k,&special);
	if(k==0)
	{
		printf("%d",n);
		return 0;
	}
	head[n].num=n;
	for(i=1;i<n;i++)
	{
		head[i].num=i;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	have=n;
	sort(head+1,head+n+1,cmp);
	for(i=1;i<=n;i++)w[head[i].num]=i;
	i=0;
	while(have>0)
		kill(++i,k);
	printf("%d",i);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
