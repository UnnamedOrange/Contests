#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;
const int MAXN=40;
int a[MAXN],b[MAXN],c[MAXN],ans[MAXN];
bool x;
int main()
{
	int i1,j1,l,m,n,t,tot,p,q,minx;
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		x=false;
		for (int i=1;i<=24;i++) scanf("%d",&a[i]);
		for (int i=1;i<=24;i++) scanf("%d",&b[i]);
		memset(c,0,sizeof(c));
		for (int i=1;i<=24;i++) 
			for (int j=0;j<=7;j++)
				if(i+j>24) c[i+j-24]+=b[i];
					else c[i+j]+=b[i];
		for (int i=1;i<=24;i++) 
			if (a[i]>c[i]) {x=true;printf("-1\n");break;}
		if (x) continue;
		for (int i=1;i<=8;i++)
			if (a[i]!=0) {x=true;break;}
		memset(ans,0,sizeof(ans));
		tot=0;
		if (!x)
		{
			memset(c,0,sizeof(c));
			for (int j=9;j<=24;j++)
			{
				for (int i=j;i>=j-7;i--)
				{
					if (c[j]>=a[j]) break;
					if (b[i]<=0) continue;
					
					if (c[j]+b[i]<=a[j]) 
					{
						ans[i]+=b[i];
						tot+=b[i];
						for (int k=i;k<=i+7;k++)if (k<=24)c[k]+=b[i];
						b[i]=0;
					}
					else
					{
						m=a[j]-c[j];
						ans[i]+=m;
						tot+=m;
						for (int k=i;k<=i+7;k++) if (k<=24) c[k]+=m;
						b[i]-=m;
					}
				}
			}
			printf("%d\n",tot);
			continue;
		}
		else
		{
			p=1;
			minx=1000;
			for (int j=1;j<=24;j++)
			{
				if (abs(c[j]-a[j])<minx)
				{
					minx=abs(c[j]-a[j]);
					p=j;
				}
			}
			for (q=p;q<=p+23;q++)
			{
				if (q>24) j1=q-24;
				else j1=q;
				
				for (l=j1;l>=j1-7;l--)
				{
					if (l>0) i1=l;
					else i1=l+24;
					
					if (c[j1]>=a[j1]) break;
					if (b[i1]<=0) continue;
					
					if (c[j1]+b[i1]<=a[j1]) 
					{
						ans[i1]+=b[i1];
						tot+=b[i1];
						for (int k=i1;k<=i1+7;k++)
							if (k<=24)c[k]+=b[i1];
							else c[k-24]+=b[i1];
						b[i1]=0;
					}
					else
					{
						m=a[j1]-c[j1];
						ans[i1]+=m;
						tot+=m;
						for (int k=i1;k<=i1+7;k++) 
							if (k<=24) c[k]+=m;
							else c[k-24]+=m;
						b[i1]-=m;
					}
				}
			}
			printf("%d\n",tot);
			continue;
		}
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
