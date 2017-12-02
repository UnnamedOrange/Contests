#include<iostream>
#include<cstdio>

using namespace std;
const int N=305;
int n,l=0,s=0,S=0,p[N]={0},b[N]={0};

inline int gcd(int x,int y)
{
	return y==0?x:gcd(y,x%y);
}

void f(int x,int t)
{
	if(x==1||l==0) 
	{
		S++;
		if(!t) s++;
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(!b[i]) {
			b[i]=1;
			l--;
			if(!t) f(gcd(p[i],x),1); 
			else f(gcd(p[i],x),0);		
			b[i]=0;
			l++;
		}
	}
	return;
}

int main()
{
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	//t1p1
	l=n;
	f(0,1);
	//cout<<S<<" "<<s;
	printf("%.9lf ",(double)(S-s)/(double)S);	
	printf("%.9lf",(double)0);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
