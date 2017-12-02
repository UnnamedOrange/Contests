#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int i,j;
int n,a[100005];
bool b[100005];
double x[3],ss;

int gcd(int a,int b)
{
	if(b>a) return gcd(b,a);
	else
	{
		a=a%b;
		if(a==0) return b;
		else return gcd(b,a);
	} 
}
void dfs(int s,int w)
{
	int i,j;
	bool tt=false;
	if(s==1) x[w]++;
	else
	{
		for(i=1;i<=n;i++)
		{
			if(b[i])
			{
				b[i]=false;
				if(w==1)
				  dfs(gcd(a[i],s),2);
				else
				  dfs(gcd(a[i],s),1);
				b[i]=true;
			}
		}
	}  
}

int main()
{
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(i=1;i<=n;i++) b[i]=true;
	for(i=1;i<=n;i++)
	{
		b[i]=false;
		dfs(a[i],1);
	    b[i]=true;
	}
	//cout<<x[1]<<' '<<x[2];
    //cout<<endl;
    ss=x[1]+x[2];
    cout<<x[2]/ss<<' '<<"1.000000";
    
    
    
    
	return 0;
}
