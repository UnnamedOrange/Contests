#include<bits/stdc++.h>
using namespace std;
int n,m,t,step,yes[500][500];
int num[1000],num2[1000];
string s[1000][1000],now,ss[10000];
string com(string s,string now)
{
	for(int q=now.length()-1,i=s.length()-1;i>=0&&q>=0;i--,q--)
	{
		if(s[i]==now[q])continue;
		else return now.substr(q+1,now.length()-q-1);
	}
	if(now.length()<s.length())return now.substr(0,now.length());
	else return s.substr(0,s.length());
}
void query()
{
	int ok=0;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)scanf("%d",&num[i]);
	if(t==1)
	{
		cout<<ss[num[1]].length()<<endl;
		return;
	}
	for(int i=2;i<=t;i++)
	{
		if(yes[num[i]][num[i-1]]&&ok)now=com(now,s[num[i]][num[i-1]]);
		else 
		{
			s[num[i]][num[i-1]]=com(ss[num[i]],ss[num[i-1]]);
			if(ok)now=com(now,s[num[i]][num[i-1]]);
			s[num[i-1]][num[i]]=s[num[i]][num[i-1]];
			yes[num[i-1]][num[i]]=1;
			yes[num[i]][num[i-1]]=1;
			if(!ok)
			{
				ok=1;
				now=s[num[i]][num[i-1]];
			}
		}
		if(now.length()==0)
		{
			cout<<0<<endl;
			return;
		}
	}
	cout<<now.length()<<endl;
}
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>ss[i];
	for(int i=1;i<=m;i++)
	{
		cin>>step;
		if(step==1)cin>>ss[++n];
		else query();
	}
	return 0;
}
