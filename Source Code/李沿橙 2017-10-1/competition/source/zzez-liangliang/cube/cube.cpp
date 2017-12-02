#include<cstdio>
#include<iostream>
#include<stack>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>

using namespace std;

int p;
stack <int> sta[30004];
int len[30004];//the length of stack[i]
int high[30004],whic[30004];//the area of i
char order;

void move(int from,int to)
{
	int t[30004];
	for(int i=1;i<=len[from];++i)
	{
		t[len[from]-i+1]=sta[from].top();
		sta[from].pop();
	}
	for(int i=1;i<=len[from];++i)
	{
		whic[t[i]]=to;
		high[t[i]]=len[to]+i;
		sta[to].push(t[i]);
	}
	len[to]+=len[from];
	len[from]=0;
	return;
}

int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int a,b;
	for(int i=1;i<=30000;++i)
	{
		len[i]=high[i]=1;
		whic[i]=i;
		sta[i].push(i);
	}
	scanf("%d",&p);
	for(int i=1;i<=p;++i)
	{
		cin>>order;
		if(order=='M')
		{
			scanf("%d%d",&a,&b);
			move(whic[a],whic[b]);
		}
		else
		{
			scanf("%d",&a);
			printf("%d\n",high[a]-1);
		}
	}
	return 0;
}
