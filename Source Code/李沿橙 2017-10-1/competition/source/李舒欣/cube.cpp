#include<bits/stdc++.h>
using namespace std;
stack<int>s[30000];
stack<int>tem;
int h[30000],p,st[30000],x,p2,num2,v,y;
char step;
int get()
{
	cin>>x>>y;
	int num=st[x];
	while(!s[num].empty())
	{
		int q=s[num].top();
		s[num].pop();
		tem.push(q);
	}
	num=st[y];
	num2=s[num].top();
	v=h[num2]+1,p2=tem.top();
	while(!tem.empty())
	{
		p2=tem.top();
		s[num].push(p2);
		st[p2]=num;
		h[p2]+=v;
		tem.pop();
	}
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	cin>>p;
	for(int i=1;i<=30000;i++)
	{
		s[i].push(i);
		st[i]=i;
	}
	tem.pop();
	for(int i=1;i<=p;i++)
	{
		cin>>step;
		if(step=='M')get();
		else cin>>x,cout<<h[x]<<endl;
	}
	return 0;
}
