#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

const int N=210;
const int M=200*25*20+10;
int n,a[N],b[N],c[N],d[N];
int f[M],m,ans;
int q[M],qf[M],ll,rr;

void work()
{
	int i,j,k;
	for (i=1;i<=n;i++)
		for (j=0;j<c[i];j++)
		{
			ll=1;rr=0;
			for (k=j;k<=m;k+=c[i])
			{
				if (ll<=rr&&k-q[ll]==(b[i]+1)*c[i])ll++;
				while (ll<=rr&&qf[rr]+(k-q[rr])/c[i]*d[i]<=f[k])rr--;
				q[++rr]=k;qf[rr]=f[k];
				f[k]=qf[ll]+(k-q[ll])/c[i]*d[i];
			}
		}
	cout<<ans+f[m]<<endl;
}

int main()
{
	freopen("abcd.in","r",stdin);
	freopen("abcd.out","w",stdout);
	int i;
	cin>>n;
	m=ans=0;
	for (i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i]>>c[i]>>d[i];
		b[i]-=a[i];
		m-=a[i]*c[i];
		ans+=a[i]*d[i];
	}
	for (i=1;i<=m;i++)f[i]=-1000000000;
	work();
	return 0;
}

