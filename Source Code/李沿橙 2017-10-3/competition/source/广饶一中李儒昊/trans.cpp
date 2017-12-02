#include<iostream>
#include<cstdio>
#include<cstring>

#define N 1000007

using namespace std;
int n,m,ans;
char a[N];

int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s",a);
	for(int i=0;i<n;i++)
	{
		if(!m) break;
		if(a[i]=='2' && a[i+1]=='2' && a[i+2]=='3')
		{
			if(i%2==0)
			{
				if(m%2==0) break;
				else 
				{
					a[i+1]='3';break;
				}
			}
			else
			{
				m--;
				a[i+2]='2';
				continue;
			}
		}
		else if(a[i]=='2' && a[i+1]=='3' && a[i+2]=='3')
		{
			if(i%2==1) 
			{
				a[i]='3';m--;continue;
			}
			else 
			{
				if(m%2==0) break;
				else 
				{
					a[i+1]='2';break;
				}
			}
		}
		else if(a[i]=='2' && a[i+1]=='3')
		{
			m--;
			if(i%2) a[i]='3';
			else a[i+1]='2';
		}
	}
	puts(a);
	fclose(stdin);fclose(stdout);
	return 0;
}
