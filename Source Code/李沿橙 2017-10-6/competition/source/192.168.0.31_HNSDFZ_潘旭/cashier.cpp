#include<iostream>
#include<cstdlib>

using namespace std;
int t,sum1=0,sum2=0;
int a[25],b[25];

int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		for(int j=0;j<24;j++)
		{cin>>a[i];sum1+=a[i];}
		for(int j=0;j<24;j++)
		{cin>>b[i];sum2+=b[i];}
		if(sum1%sum2)
		cout<<sum1%sum2<<endl;
		else
		cout<<"-1"<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
