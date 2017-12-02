#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;

int n,m,a[1000006],k;
int ave=0,maxa=0,time=1,maxt=0;
double av=0;

int main() 
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
    scanf("%d%d", &n, &m);
    
    for(int i=1;i<=n;++i) 
	{
        scanf("%d", &a[i]);
        av+=(double)a[i]/n;
    }
    
	for(int i=1;i<=n;++i)
	{
		if(a[i]>=maxa)
		{
			time=1;
			maxa=a[i];
			int j=i+1;
			while(a[j]==a[j-1])
				++j,++time;
			if(time>maxt)	maxt=time;
		}
	}
	
    ave = floor(av);

    for(int i = 1; i <= m; ++i) 
	{
        scanf("%d", &k);
        
        if(k>maxa) {printf("0 ");continue;}
        if(k==maxa)	{printf("%d ",maxt);continue;}
        if(k<=ave) {printf("%d ",n);continue;}
        
        int ans;
        double t1=(double)k-av;
        t1*=n;
        int t2=t1;
        ans=n-(ceil((double)t2/(1.0*k)));
        int q=ceil((double)t2/(1.0*k));
        printf("%d ",ans-2);
    }
    return 0;
}

