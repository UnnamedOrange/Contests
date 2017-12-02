#include<bits/stdc++.h>
using namespace std;
int number[10],num[10],book;
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int n,k1,k2,t,s=0,m;
	cin>>n;
	for(int i=1;i<n;i++)
	{	
		m=0;
		k1=i;
		while(k1!=0)
		{
			number[k1%10]=1;
			k1/=10;
		}
		for(int j=i+1;j<=n;j++)
		{
			m=0;
			k2=j;
			while(k2!=0)
			{
				num[k2%10]=1;
				k2/=10;
			}
			for(int x=0;x<=9;x++)
				if(number[x]!=num[x])
					m=1;
			for(int x=0;x<=9;x++)
				num[x]=0;
			if(m==0) book++;
		}
		for(int j=0;j<=9;j++)
			number[j]=0;
	}
	cout<<book;
	fclose(stdin);
	fclose(stdout);
	return 0;

}
