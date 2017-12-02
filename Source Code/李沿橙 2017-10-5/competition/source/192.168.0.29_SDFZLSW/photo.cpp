#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;
int n,m,k,dp[2005]={0};
inline int c(int x,int y)
{
	long long a=1;
	for(int i=y+1;i<=x;i++)
	{
		a*=i;
		a=a%1000000007;	
	}
	for(int i=2;i<=x-y;i++) a/=i;
	//cout<<a<<endl;	
	return a;
}
int main()
{
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	int p;	
	scanf("%d%d%d",&n,&m,&k);
	long long q;
	dp[1]=k;		
	for(int i=2;i<=k;i++)
	{
		p=0;
		q=(int)pow(i,n)%1000000007;
		for(int j=1;j<i;j++) p+=dp[j]*c(i,j)/2;
		//cout<<q<<" "<<p<<endl;	
		dp[i]=q-p;
	}
	int l=0
	for(int i=1;i<=k;i++) l+=(int)pow(dp[i],m)%1000000007;
	cout<<l;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
