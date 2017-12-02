#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

#define N 100007

using namespace std;
int n,m,cnt;
int X[N],Y[N];
double k,x,y,b,dis2;
struct segment
{
	double k,b;
}e[N<<1];

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

double work(double x,double y)
{
	return sqrt(double(x)*double(x)+double(y)*double(y));
}

int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++) X[i]=read();
	for(int i=1;i<=n;i++) Y[i]=read();
	sort(X+1,X+n+1);sort(Y+1,Y+n+1);
	for(int i=1;i<=n;i++)
	{
		e[i].k=double(Y[i])/-double(X[i]);
		e[i].b=Y[i]; 
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		x=read();y=read();
		if(x==0)
		{
			int l=1,r=n,mid;
			while(l<=r)
			{
				mid=l+r>>1;
				if(Y[mid]>=y) cnt=mid,l=mid+1;
				else r=mid-1;
			} 
		}
		double dis1=work(double(x),double(y));
		k=double(y)/double(x);
		int l=1,r=n,mid;
		while(l<=r)
		{
			mid=l+r>>1;
			if(work(double(e[mid].b/(k-e[mid].k)),k*double(e[mid].b/(k-e[mid].k)))<=dis1)
			  cnt=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",cnt);
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
