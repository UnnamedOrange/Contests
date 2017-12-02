#include<bits/stdc++.h>
using namespace std;
queue<int> que[30001];
int where[30001],tque[40000];
inline void clear(int n)
{
	int l=que[n].size();
	for(int i=1;i<=l;i++)
	{
		que[n].pop();
	}
	for(int i=1;i<=l;i++)
	{
		que[n].push(tque[i]);
	}
	return;
}
inline void qcopy(int n)
{
	int l=que[n].size();
	for(int i=1;i<=l;i++)
	{
		tque[i]=que[n].front();
		que[n].pop();
	}
	for(int i=1;i<=l;i++)
	{
		que[n].push(tque[i]);
	}
	return;
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	int p,t1,t2,t=0,l;
	cin>>p;
	for(int i=1;i<=30000;i++)
	{
		where[i]=i;
		que[i].push(i);
	}
	for(int i=1;i<=p;i++)
	{
		char c;
		cin>>c;
		if(c == 'M')
		{
			int x,y,t;
			cin>>x>>y;
			x=where[x];y=where[y];
			l=que[y].size();
			for(int k=1;k<=l;k++)
			{
				t=que[y].front();
				where[t]=x;
				que[y].pop();
				que[x].push(t);	
			}
			/*qcopy(x);
			for(int k=1;k<=que[x.size])*/
		}
		if(c == 'C')
		{
			cin>>t1;
			int w=where[t1];
			qcopy(w);
			l=que[w].size();
			for(int j=1;j<=l;j++)
			{
				if(que[w].front()==t1)
				{
					cout<<que[w].size()-1<<endl;
					clear(w);//¸´Ô­que[w]; 
					break;
				}
				else que[w].pop();
			}
		}
	}
	return 0;
}
