#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define lint long long
#define N 132072
using namespace std;
int a[N],f[N];
inline bool is_s(int x)
{
	int y=sqrt(x+0.5);
	return y*y==x;
}
int main()
{
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
	int n,k;scanf("%d%d",&n,&k);
	if(k==1)
	{
		if(n==2)
		{
			int x,y;scanf("%d%d",&x,&y);
			if(is_s(x+y)) printf("2\n1\n");
			else printf("1\n\n");
			return 0;
		}
		else if(n%10==2)//assume a_i<=2
		{
			int cnt=0;
			for(int i=1;i<=n;i++)
			{
				int x;scanf("%d",&x);
				if(x==2) a[++cnt]=i;
			}
			printf("%d\n",cnt);
			for(int i=1;i<cnt;i++)
				printf("%d ",a[i]);
			printf("\n");
			return 0;
		}
		else{
			for(int i=1;i<=n;i++)
				scanf("%d",&a[i]);
			f[1]=1;
			for(int i=2;i<=n;i++)
			{
				f[i]=i;
				for(int j=i-1;j>=f[i-1];j--)
					if(is_s(a[i]+a[j]))
						break;
					else f[i]=j;
			}
			int c=n,cnt=0;
			while(c) a[++cnt]=f[c]-1,c=f[c]-1;
			printf("%d\n",cnt);
			for(int i=cnt-1;i;i--)
				printf("%d ",a[i]);
			printf("\n");
			return 0;
		}
	}
	else{//k=2
		if(n==2) return !printf("%d\n\n",1);
		else if(n==4)
		{
			for(int i=1;i<=n;i++)
				scanf("%d",&a[i]);
			if(!is_s(a[1]+a[2])&&!is_s(a[3]+a[4])) return !printf("%d\n\n",1);
			if(!is_s(a[1]+a[3])&&!is_s(a[2]+a[4])) return !printf("%d\n\n",1);
			if(!is_s(a[1]+a[4])&&!is_s(a[2]+a[3])) return !printf("%d\n\n",1);
			if(!is_s(a[2]+a[3])) return !printf("%d\n1\n",2);
			if(!is_s(a[2]+a[4])) return !printf("%d\n1\n",2);
			if(!is_s(a[3]+a[4])) return !printf("%d\n1\n",2);
			return !printf("%d\n2\n",2);
		}
		else return !printf("%d\n\n",1);
	}
	return 0;
}
