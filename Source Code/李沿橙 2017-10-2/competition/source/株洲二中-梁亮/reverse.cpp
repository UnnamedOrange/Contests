#include<cstdio>
#include<iostream>

using namespace std;
int chuan[100004],color[100004];
int ze=0,on=0,ans=0;
int p1,p0,m1,m0;
int sta1,sta0;
int len=0;
void input()
{
	char c1,c2;
	int t[100004],tx=0;
	while(cin>>c1)
	{
		t[++tx]=c1-'0';
		if(t[tx]==0)	++ze;
		else	++on;
	}
	int t1=1,t2=0;
	for(int i=1;i<tx;++i)
	{
		if(t[i]==t[i+1])
			++t1;
		else
		{
			chuan[++t2]=t1;
			color[t2]=t[i];
			++len;
			t1=1;
		}
	}
	chuan[++t2]=t1;
	color[t2]=t[tx];
	++len;
	return;
}

int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	input();
	sta1=1;sta0=len;
	do
	{
		for(int i=sta1;i<=len;++i)
		{
			if(color[i]==1)
			{
				p1=i;
				sta1=i;
				break;
			}
		}
		for(int i=sta0;i>=1;--i)
		{
			if(color[i]==0)
			{
				p0=i;
				sta0=i;
				break;
			}
		}
		if(p1==p0+1)	break;
		if(chuan[p1]>chuan[p0])
		{
			ze-=chuan[p0];
			ans+=chuan[p0];
			color[p0]=1;
		}
		else
		{
			on-=chuan[p1];
			ans+=chuan[p1];
			color[p1]=0;
		}
	}while(ze>0&&on>0);
	printf("%d",ans);
	return 0;
}
