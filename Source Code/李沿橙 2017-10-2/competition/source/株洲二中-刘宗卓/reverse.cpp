#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char num[100005]={0};
int ans=0;
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int a;
	int i=0,j=0;
	gets(num);
	j=strlen(num);
	
	a=j;
	if(a%2==0)	
	{
		while(i!=j)
		{
			if(num[i]=='1')
			{
			num[i]='0';
			ans++;
			}
			
			if(num[j]=='0')
			{
			num[j]='1';
			ans++;
			}
			i++;
			j--;
			if(i==a/2&&j==a/2) break;
		}
	}
	else if(a%2==1)
	{
		j--;
		while(1)
		{
			if(num[i]=='1'&&i!=a/2)
			{
			num[i]='0';
			ans++;
			}
			
			if(num[j]=='0'&&j!=a/2)
			{
			num[j]='1';
			ans++;
			}
			i++;
			j--;
			if(i==(a-1)/2&&j==(a-1)/2) break;
		}
	}

			
	fclose(stdin);
	fclose(stdout);
	cout<<ans;
	return 0;

}
