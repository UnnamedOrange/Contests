#include<cstdio>
#include<cstdlib>
#include<cctype>
using namespace std;
#define MAXN 1000005
int n,m,len;
int cf[MAXN+1],a[MAXN+1],c[MAXN+1];
int read()
{
    int x=0; char ch=getchar();
    bool flag=0;
    while (ch<'0'||ch>'9') { if (ch=='-') flag=1; ch=getchar(); }
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    if (flag) return -x; else return x;
}
int lowbit(int x)
{
	return x & (-x); 
}
void updata(int x,int k)//点修改 
{
	while(x <= n)
	{
		c[x]+=k;
		x+=lowbit(x);
	}
}
long long sum(int x)//计算区间和 
{
	long long tot=0;
	while(x > 0)
	{
		tot+=c[x];
		x-=lowbit(x);
	}
	return tot;//x == 0时tot为0 
}
//本题可以理解为计算一段区间和>0的区间的最大长度 
int main()
{
	freopen("blocks.in","r",stdin);
    freopen("blocks.out","w",stdout);
    n=read();
    m=read();
	//scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		//scanf("%d",&a[i]);
		a[i] = read();
		updata(i,a[i]);
		}		
	for(int i=1;i<=m;i++)
	{
		int k;
		//scanf("%d",&k);
		k=read();
		/*for(int j=1;j<=n;j++)
			cf[j] = a[j] - k;*/
		//ycl(k);
		/*for(int j=1;j<=n;j++)
			updata(j,cf[j]);*/
		//printf("%d %d %d\n",sum(1),sum(0),sum(1)-sum(0));
		for(int st=1;st<=n;st++)//<=n???
			for(int ed=st;ed<=n;ed++){
				int temp = ed - st + 1;
				if((sum(ed)-sum(st-1)-temp*k) >= 0){
					//int temp = ed - st + 1;	
					//printf("%d %d %d\n",sum(ed),sum(st-1),temp);
					if(temp > len)
						len = temp;
				}
			}
		printf("%d ",len);
		len = 0;//清零操作 
		//最后-区间长度*k 会更优秀 
		//printf("%lld\n",sum(y)-sum(x-1));
	}
        return 0;
}
//后缀和？？ 
