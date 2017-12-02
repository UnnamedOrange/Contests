#include<bits/stdc++.h>
using namespace std;
int n;long long f[70],a,b,ans;
void searchans()
{
	int i1=2,i2=2;long long key1=2,key2=2,maxn;
	while(key1<a)key1+=f[i1],i1++;
	while(key2<b)key2+=f[i2],i2++;	
	if(f[i1-1]-key1+a==f[i2-1]-key2+b)ans=f[i1-1]-key1+a;//如果祖先相同 
	else if(f[i1-1]-key1+a==b)ans=b;//如果a的祖先是b 
	else if(f[i2-1]-key2+b==a)ans=a;//如果b的祖先是a 
	else if(f[i1-1]-key1+a>f[i2-1]-key2+b)//优先祖先大的跳 
	{
		a=f[i1-1]-key1+a;
		searchans();
	}
	else if(f[i1-1]-key1+a<f[i2-1]-key2+b)
	{
		b=f[i2-1]-key2+b;
		searchans();
	}
}
int main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	int i;
	scanf("%d",&n);
	f[1]=1;
	f[2]=1;
	for(i=3;i<=60;i++)
		f[i]=f[i-1]+f[i-2];
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a,&b);
		if(abs(a-b)==1)ans=1;//可以省时间但是有待证明？？？ 
		else if(a!=b)searchans();	
		else ans=a;//如果相同就不搜了 
		printf("%lld\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
