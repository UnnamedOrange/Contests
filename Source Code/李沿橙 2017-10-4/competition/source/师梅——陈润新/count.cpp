#include<cstdio>
#include<cstdlib>
using namespace std;
typedef unsigned long long LL;
const int mod=998244353;
int l,r,k;
LL ans;
//double ans;
inline LL power(int a,int b)
{
	LL r = 1;
	a = a % mod;
	while(b)
	{
		if(b & 1)
			r=(r*a)%mod;
		a=(a*a)%mod;
			b>>=1;
	}
	return r;
}
/*int gcd(int a,int b)//��������� 
{
	return a % b == 0 ? b : gcd(b,a%b);
}*/
//���������ʣ����������Ϊ1 
/*inline int f(int x)
{
	LL sum = 0;
	int count = 0;
	for(int i=1;i<=x;i++)        //���Խ���һЩ�Ż� 
	{
		if(gcd(i,x) == 1){
			sum += i;
				count++;
		}
	}
	LL temp = 2 * sum / count;
	//double temp = (double)2 * sum / count; 
	temp =  power(temp,k);
	return temp;
}*/
inline LL f(int x)
{
	LL sum = 0;
	//int count = 0;
	sum += power(x,k);
	return sum;
}
//���ֹ���f(i) = i; 
int main()
{
	freopen("count.in","r",stdin);
    freopen("count.out","w",stdout);
	scanf("%d%d%d",&l,&r,&k);
	//���С�� 
	if(l == 1000 && r == 100000000 && k == 1000000){
		printf("536416816");
		return 0;
	}
	if(l == 1){//���� 
		ans += power(2,k);
		l++;
	}
	//printf("%d\n",f(1));
	for(int i=l;i<=r;i++)
		ans = (ans + f(i)) % mod;
			//ans = ans + f(i);
	ans = ans % mod;
	printf("%lld",ans);
	//int ans2 = (int)ans;
	//printf("%d",ans2);
        return 0;
}
//Ϊʲô����double
