#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;
const int len=100000+50;
int s[len]={0},num[len]={0},x[len]={0},y[len]={0};
char c[len]={0};
int l,n=0,m,t=0,z=0,o=0,ans=0;

void deal(int t)
{
	if(t>1)
	{
		if(!num[t])
		deal(t-1);
		else
		{
			if(s[t]>=s[t+1]) {num[t+1]=1;ans+=s[t+1];}
			else
			{
				if(y[t]+s[t]<=x[t+1]) {ans+=y[t+1];return;}
				else {num[t+1]=1;ans+=s[t+1];}
			}
			deal(t-1);
		}
	}
}

int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%s",c);
	m=c[0]-'0';
	l=strlen(c);
	for(int i=0;i<=l;i++)
	{
		if(i!=l)
		{
			if(m==c[i]-'0')
			n++;
			else
			{
				s[++t]=n;
				num[t]=m;
				x[t]+=z;
				y[t]+=o;
				if(c[i-1]-'0')
				o+=n;
				else
				{
					if(t!=1)
					z+=n;
				}
				n=1;
				m=c[i]-'0';
			}
		}
		else
		{
			s[++t]=n;
			num[t]=m;
			x[t]+=z;
			y[t]+=o;
		}
	}
	deal(t-1);
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
