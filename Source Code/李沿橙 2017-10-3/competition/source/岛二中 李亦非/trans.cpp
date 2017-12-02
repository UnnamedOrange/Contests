#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
char a[1010101];
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	int n,k,tmp,i;
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		scanf("%s",a+1);
		tmp=0;
		for(i=1;i<n;i++)
		{
			if(a[i]=='2'&&a[i+1]=='3')
			{
				if(i%2==0)
				{
					if(a[i-1]=='2')
						break;
					a[i]++;
					tmp++;
				}
				else
				{	
					a[i+1]--;
					tmp++;
				}
				if(tmp>=k)
					break;
			}
			
		}
		if(tmp<k)
			a[i]=a[i]+(k-tmp)%2;
		for(i=1;i<=n;i++)
			printf("%c",a[i]);
		printf("\n");
	}
	return 0;
}

