#include<iostream>
#include<cstdio>
using namespace std;
int f[30005];
int s[30005];
int m[30005];
int ans[30005];
int i,j,n,p,x,y,t;
int t1,t2;
char c;
void ss(int x)
{
	m[x]=m[s[x]]+1;
	if(f[x]!=x) ss(f[x]);
}
int bb(int x)
{
	if(f[x]==x) return x;
		else return bb(f[x]);
}
int zz(int x)
{
	if(s[x]==x) return x;
		else return zz(s[x]);
}
int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	cin>>p;
	for(i=1;i<=30000;i++)
		f[i]=i,s[i]=i;
	for(j=1;j<=p;j++)
	{
		cin>>c;
		if(c=='M')
		{
			cin>>x>>y;
			t1=bb(y);
			t2=zz(x);
			f[t1]=t2;
			s[t2]=t1;
			ss(t2);
		}
		else
		{
			cin>>x;
			t++;
			ans[t]=m[x];
			
		}
		
	}
	for(i=1;i<=t;i++) cout<<ans[i]<<endl;
	return 0;
}