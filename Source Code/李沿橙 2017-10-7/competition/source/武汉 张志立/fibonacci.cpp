#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int i,j,m,n;
int a[100005],b[100005];
int tt,t,s;
int fi[100005];
int f[1000005],ff[1000005];
int ma;
int t1,t2;
int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	cin>>m;
	for(i=1;i<=m;i++)
	{
		cin>>a[i]>>b[i];
		if(a[i]>ma) ma=a[i];
		if(b[i]>ma) ma=b[i];
	}
	f[1]=1;
	ff[1]=1;
	fi[1]=1;
	fi[2]=1;
	tt=0;
	t=2;
	for(i=3;i<=100005;i++) fi[i]=fi[i-1]+fi[i-2];
	while(t<=ma)
	{
	    tt++;
		for(i=1;i<=fi[tt];i++)
		{	
			f[t]=i;
			t++;
		}
    }
    //for(i=1;i<=15;i++) cout<<f[i];
    for(i=1;i<=m;i++)
    {
       t1=a[i];
       t2=b[i];
       while(t1!=t2)
       {
       		if(t1<t2) t2=f[t2];
       		else t1=f[t1];
       }
       cout<<t1<<endl;
       
    }
	return 0;
}
