#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int n,k,i,j,s,t,d[1000005],b[1000005],x;		
string a;
int search(int t)
{
	while(!b[t])
	{
		t++;
		if(t>n) break;
	}
	if(t>n) return -1;
	else return t;
}
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(cin>>n)
	{
		cin>>k;
        cin>>a;
		for(i=0;i<=n-1;i++)
		{
			d[i+1]=a[i]-'0';
			if(d[i+1]==3 && d[i]==2) b[i]=1;	
		}
		t=1;
		for(i=1;i<=k;i++)
		{
			x=search(t);
			if(x==-1) break;
			if(x%2==1) 
			{
				d[x+1]=2;
				if(d[x+2]==3) b[x+1]=1;
			}
			else
			{
				d[x]=3;
				if(d[x-1]==2) b[x-1]=1;
			}
			b[x]=0;
			t=x-1;
		}
		
		for(i=1;i<=n;i++)  cout<<d[i];
	}	
	return 0;
}
