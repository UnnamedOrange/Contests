#include<bits/stdc++.h>
using namespace std;
int n,m,k,color;long long m1,ans1,ans2,ans,c,co;//c存每列的前k个的排放方法,co是从color中取k个的方案 
/*推导公式：k=1~color，(k^(n-k)*(!color-!(color-k)))^m,
co=!color-!(color-k)可以简化，如k=1时，co=color；k=2时，co=color*(color-1)=co*(color-1),
以此类推*/
long long count(long long x)//求阶乘 
{ 
	int i,key=x;
	for(i=2;i<key;i++)x=(x*i)%1000000007;
	//若爆，防爆措施：分解，在乘的时候就分别%
	return x; 
}
long long q(long long x)//快速幂 
{
	int i,t=1,key=x;
	i=n-k-1;
	if(i==-1)return 1;
//	else if(i==1)return x;
	while(i>=t)
		x=(x*x)%1000000007,i-=t,t+=t;
	while(i>0)x=(x*key)%1000000007,i--;
	return x;
}
long long qq(long long x)
{
	int i=m-1,key=x,t=1;
	while(i>=t)
		x=(x*x)%1000000007,i-=t,t+=t;
	while(i>0)x=(x*key)%1000000007,i--;
	return x;
}
int main()
{
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);
	int i;
	scanf("%d%d%d",&n,&m,&color);
	co=1;
	m1=count(m); 
	for(k=1;k<=min(color,n);k++)//k超过n 
	{
		co=co*(color-k+1)%1000000007; 
		ans=(ans+qq(q(k)*co))%1000000007;
	}
	printf("%lld",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
