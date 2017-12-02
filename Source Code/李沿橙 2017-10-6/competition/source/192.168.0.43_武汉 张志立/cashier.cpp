#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int i,j,n,m;
int s,h;
int t,tt;
int a[100],b[100];
int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	cin>>t;
	for(int h=1;h<=t;h++)
	{
		s=0;
		for(i=1;i<=24;i++)
		{
			cin>>a[i];
		}
		for(i=1;i<=24;i++)
		{
			cin>>b[i];
		}
		for(i=8;i<=24;i++)
		{
			if(a[i]>0)
			{
				int tt=i;
				while(a[i]>0 && i-tt<=7 && tt>0)
				{
					if(b[tt]>0)
					{
						if(b[tt]>a[i]) 
						{
							for(j=i+1;j<=tt+7;j++)
						    {
						  	  a[j]-=a[i];
							  if(a[j]<0) a[j]=0;
							}
							s+=a[i];
							b[tt]-=a[i];
							a[i]=0;
						}
						else 
						{
							for(j=i+1;j<=tt+7;j++)
							{
								a[j]-=b[tt];
								if(a[j]<0) a[j]=0;		
							}
							s+=b[tt];
							a[i]-=b[tt];
							b[tt]=0;
						}
					}
			 		tt--;
				}
				if(a[i]!=0) s=-9999999;
			}
			//for(j=1;j<=24;j++) cout<<a[j]<<' ';
			//cout<<endl<<endl;
			//for(j=1;j<=24;j++) cout<<b[j]<<' ';
			
			//cout<<endl<<endl;
		}
	
		if(s>0) cout<<s;
		else cout<<-1;
		cout<<endl;
	}
	return 0;
}
