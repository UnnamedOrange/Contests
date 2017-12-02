#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,i,j,k,t,s;
int bb[1005][10];
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++)
	{
		t=i;
		while(t>0) bb[i][t%10]=1,t=t/10;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=i-1;j++)
		{	
			int b=true;
			for(k=0;k<=9;k++)
			{
				b=b&&(bb[i][k]==bb[j][k]);
			}	
			if(b) s++;
		}		
	}
	cout<<s;
	return 0;
}