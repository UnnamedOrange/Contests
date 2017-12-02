#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m,x,i,j,k,tt;
char a[105][105];
int l[105];
int b[105];
string s;
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	cin>>n>>m;
	for(j=1;j<=n;j++)
	{
		cin>>s;
		l[j]=s.size();
		for(i=0;i<=l[j]-1;i++)
		{
			a[j][i]=s[i];		
		}
	}
	for(j=1;j<=m;j++)
	{
		cin>>x;
		if(x==1) 
		{
			cin>>s;
			l[++n]=s.size();
			for(i=0;i<=l[n]-1;i++)
			   a[n][i]=s[i];
		}
		else
		{
			cin>>tt;
			bool bb=true;
			int mm=999999;
			for(i=1;i<=tt;i++)
			{
				cin>>b[i];
			}
			for(i=1;i<=tt;i++)
			{
				mm=min(mm,l[b[i]]);
			}
			k=0;
			while(bb && k<=mm)
			{
				char test=a[b[1]][l[b[1]]-k-1];
				for(i=2;i<=tt;i++)
				{
					if(a[b[i]][l[b[i]]-k-1]!=test) bb=false;
				}
				k++;
			}
			k--;
			cout<<k;
		}
		
	}
	return 0;
}

