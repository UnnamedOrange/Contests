#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int i,j,p;
int x[1005],y[1005];
int n;
long long k,a[1005];
bool bb[1005][1005];
bool hh[1005][1005];
int f[1005];
int r[1005];
long long m[1005];
long long s;
const long long mm=1000000007;


int bcj(int a)
{
	if(f[a]==a) return a;
	else return bcj(f[a]);
}


void js(int a)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(bb[i][a] && hh[i][a])
        {
            f[i]=a;
			hh[i][a]=hh[a][i]=false;
			js(i);
			hh[i][a]=hh[a][i]=true;
		}
	}
}



void zj(int b,long long s)
{
	int j;
    if(s>m[r[b]]) m[r[b]]=s;
	for(j=1;j<=n;j++)
	{
		if(bb[b][j] && hh[b][j])
		{
			//cout<<j<<' '<<s<<' ';
			hh[b][j]=hh[j][b]=false;
			zj(j,(s+a[j])%mm);
			hh[b][j]=hh[j][b]=true;
		}
	}
	
}



int main()
{
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n-1;i++)
	{
		cin>>x[i]>>y[i];
		bb[y[i]][x[i]]=bb[x[i]][y[i]]=true;
	}
    for(i=1;i<=n;i++)
    {
    	for(j=1;j<=n;j++) hh[i][j]=true;
    }
    for(i=1;i<=n;i++)
	   r[i]=1;
    js(1);
	//for(i=1;i<=n;i++) cout<<f[i]<<' '; 
	//for(i=1;i<=n;i++) cout<<r[i];
	//cout<<endl;
	f[1]=1;
	
	for(i=1;i<=n;i++)
	   zj(i,a[i]);
	cout<<m[1]<<endl;
	for(i=1;i<=n-1;i++)
	{
		cin>>k;
	
	
		bb[y[k]][x[k]]=bb[x[k]][y[k]]=false;
		
		if(f[y[k]]==x[k]) f[y[k]]=y[k],r[y[k]]=i+1;
		else f[x[k]]=x[k],r[x[k]]=i+1;
		
		for(j=1;j<=n;j++)
		    r[j]=r[bcj(j)];
	//	for(j=1;j<=n;j++)
	//	cout<<r[j];
		//cout<<endl;
		
		for(j=1;j<=i+1;j++)
		    m[j]=0;
		
		
		for(j=1;j<=n;j++)
		{
			zj(j,a[j]);
		}
		
		//for(j=1;j<=i+1;j++)
		//  cout<<m[j]<<' ';
		//  cout<<endl;
		
		
		s=1;
		for(j=1;j<=i+1;j++)
		{
			s=s*m[j]%mm;
		}
		cout<<s<<endl;
	}
		return 0;
}
