#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
#define INF 2147483647
int T;
int a[25],b[25],smax[25];
int s[25],h[25];
using namespace std;
priority_queue <pair <int,int> > q;

struct EDGE
{
	int to;
	int next;
	int s;
}e[30];

int cnt=0;
void ADDE(int from,int to,int s)
{
	cnt++;
	e[cnt].to=to;
	e[cnt].s=s;
	e[cnt].next=h[from];
	h[from]=cnt;
}

void dij()
{
	for(int i=0;i<=7;i++) q.push(make_pair(s[i],i));
	while(!q.empty())
	{
		int p=q.top().second;
		q.pop();
		for(int i=h[p];i;i=e[i].next)
		{
			if(s[p]+e[i].s>s[e[i].to] && s[p]+e[i].s<=smax[e[i].to])
			{
				s[e[i].to]=s[p]+e[i].s;
				q.push(make_pair(s[e[i].to],e[i].to));
			}
		}
		
	}
}

int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d",&T);
	for(int I=1;I<=T;I++)
	{
		for(int i=0;i<=23;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i=0;i<=23;i++)
		{
			scanf("%d",&b[i]);
		}
		for(int i=24-7;i<=24;i++) smax[0]+=b[i%24];
		for(int i=1;i<=23;i++)
		{
			if(i<8) smax[i]=smax[i-1]+b[i]-b[i-8+24];
			else smax[i]=smax[i-1]+b[i]-b[i-8];
		}
		for(int i=0;i<=23;i++)
		{
			int numto=(i+8)%24;
			ADDE(i,numto,a[numto]);
		}
		dij();
		int ans=0,maxs=0;
		for(int i=0;i<=7;i++)
		{
			int mx=INF,tot=0;
			for(int j=i;j<=23;j+=8)
			{
				if(smax[j]-s[j]<mx) mx=smax[j]-s[j];
				tot+=s[j];
			}
			tot+=3*mx;
		}
		cout<<endl;
		cout<<mx<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
