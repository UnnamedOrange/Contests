#include <bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int t;
int need[60];
int have[60];
void doit()
{	int n=0;
	for(int i=0;i<24;i++)need[i]=read();
	for(int i=0;i<24;i++)have[i]=read();
	int a[60],le=0;
	for(int i=17;i<=23;i++)le+=have[i];le+=have[0];
	a[0]=le;
	for(int i=1,j=17;i<24;i++,j++)
	{
		j%=24;le-=have[j];le+=have[i];a[i]=le;
	}
	for(int i=0;i<24;i++)a[i]-=need[i];
	for(int i=0;i<24;i++)if(a[i]<0){printf("-1");return;}
	//for(int i=0;i<24;i++)cout<<have[i]<<" ";cout<<endl;
	for(int i=0;i<24;i++)
	{
		int miD=have[i];
		for(int j=i,x=1;x<=8;j++,x++)
		{j%=24;
			miD=min(miD,a[j]);
		}
		have[i]-=miD;
		for(int j=i,x=1;x<=8;j++,x++)
		{j%=24;
			a[j]-=miD;
		}
	}
	//for(int i=0;i<24;i++)cout<<have[i]<<" ";
	for(int i=0;i<24;i++)n+=have[i];
	printf("%d\n",n);
}
int main()
{	
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	t=read();
	for(int i=1;i<=t;i++)doit();
	return 0;
}
