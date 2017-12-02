#include<algorithm>
#include<iostream>
#include<cstdio>

using namespace std;
const int m=998244353;
inline int gcd(int a,int b) { return b==0?a:gcd(b,a%b); }
inline int qow(int a,int k) { long long s=1; for(int i=1;i<=k;i++) s*=(a%m),s=s%m;return s%m;}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int l,r,k,p,s,S=0;
	scanf("%d%dss%d",&l,&r,&k);	
	if(l==r&&l==1)
	{
		printf("2");
		fclose(stdin);
		fclose(stdout);
		exit(0);
	}	
	for(int i=l;i<=r;i++) 
	{
		p=0,s=0;
		for(int j=1;j<=i;j++)
 			if(gcd(i,j)==1)
				s+=j,p++;
		//cout<<s<<" "<<p<<" "<<(double)s/(double)p<<endl;
		S+=qow(((double)s/(double)p)*2,k);
		S%=m;
	}
	printf("%d",S);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
