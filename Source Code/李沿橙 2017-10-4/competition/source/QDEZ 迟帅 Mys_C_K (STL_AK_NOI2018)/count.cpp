#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 998244353
#define N 1000010
#define K 110
#define lint long long
using namespace std;
inline int fast_pow(int b,int k)
{
	int ans=1;
	while(k)
	{
		if(k&1) ans=(lint)ans*b%mod;
		b=(lint)b*b%mod;k>>=1;
	}
	return ans;
}
int f[N],pri[80498],cnt;
bool notp[N];
int fac[K],facinv[K];
inline int getInv(int n)
{
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=(lint)fac[i-1]*i%mod;
	facinv[n]=fast_pow(fac[n],mod-2);
	for(int i=n-1;i>=0;i--)
		facinv[i]=(lint)facinv[i+1]*(i+1)%mod;
	return 0;
}
inline int getC(int n,int m)
{
	if(m>n) return 0;
	return (lint)fac[n]*facinv[m]%mod*facinv[n-m]%mod;
}
struct matrix{
	int v[K][K],n,m;
	matrix(int _n=0,int _m=0)
	{
		n=_n;m=_m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				this->v[i][j]=0;
	}
	inline matrix clear(int _n=0,int _m=0)
	{
		n=_n;m=_m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				this->v[i][j]=0;
		return *this;
	}
	inline matrix operator=(const matrix &A)
	{
		this->n=A.n;this->m=A.m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				this->v[i][j]=A.v[i][j];
		return *this;
	}
	inline matrix operator*(const matrix &b)
	{
		int p=b.m;
		matrix &a=*this,c(n,p);
		for(int i=1;i<=n;i++)
			for(int k=1;k<=p;k++)
				for(int j=1;j<=m;j++)
					(c.v[i][k]+=(lint)a.v[i][j]*b.v[j][k]%mod)%=mod;
		return c;
	}
	inline matrix operator*=(const matrix &a)
	{
		return (*this)=this->operator*(a);
	}
}A,B,T;
inline int out(const matrix &A)
{
	int n=A.n,m=A.m;
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=1;j<=m;j++)
			cout<<A.v[i][j]<<" ";
	return 0;
}
inline matrix getI(int n)
{
	matrix B(n);
	for(int i=1;i<=n;i++)
		B.v[i][i]=1;
	return B;
}
inline matrix fast_pow(matrix &B,int k)
{
	T=B;k--;
	while(k)
	{
		if(k&1) T*=B;
		B*=B;k>>=1;
	}
	return T;
}
inline int getA(matrix &A,int k)
{
	A.clear(k+2,k+2);
	for(int i=1,p=0;i<=k+1;i++,p++)
		for(int j=1;j<=k-p+1;j++)
			A.v[i][p+j]=getC(k-p,j-1);
	for(int i=1;i<=k+1;i++)
		A.v[k+2][i]=A.v[1][i];
	A.v[k+2][k+2]=1;
	return 0;
}
inline int getB(matrix &B,int k)
{
	B.clear(k+2,1);
	for(int i=1;i<=k+2;i++)
		B.v[i][1]=1;
	return 0;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int L,R,k;scanf("%d%d%d",&L,&R,&k);
	int n=R;f[1]=fast_pow(2,k);
	if(k<=100&&R>1000000)
	{
		getInv(k);int ans1,ans2;
		getA(A,k);getB(B,k);
		if(R==1) ans1=f[1];
		else B=fast_pow(A,R-1)*B,ans1=B.v[k+2][1]-1+f[1];
		getA(A,k);getB(B,k);
		if(L==1) ans2=0;
		else if(L==2) ans2=f[1];
		else B=fast_pow(A,L-2)*B,ans2=B.v[k+2][1]-1+f[1];
		ans1%=mod;(ans1+=mod)%=mod;
		ans2%=mod;(ans2+=mod)%=mod;
		(ans1+=mod-ans2)%=mod;
		printf("%d\n",ans1);
		return 0;
	}
	for(int i=2;i<=n;i++)
	{
		if(!notp[i]) pri[++cnt]=i,f[i]=fast_pow(i,k);
		for(int j=1;j<=cnt;j++)
		{
			if((lint)i*pri[j]>n) break;
			notp[i*pri[j]]=true;
			f[i*pri[j]]=(lint)f[i]*f[pri[j]]%mod;
			if(i%pri[j]==0) break;
		}
	}
	for(int i=1;i<=n;i++)
		(f[i]+=f[i-1])%=mod;
	printf("%d\n",(f[R]-f[L-1]+mod)%mod);
	return 0;
}
