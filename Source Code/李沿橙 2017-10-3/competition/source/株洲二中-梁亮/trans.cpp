#include<cstdio>
#include<iostream>

using namespace std;
int n,k;
char a[1000004];
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(cin>>n)
	{
		scanf("%d",&k);
		for(int i=1;i<=n;++i)
			cin>>a[i];
			for(int i=1;i<=n;++i)
			{
				if(k==0)	break;
				if(a[i]=='2'&&a[i+1]=='3')
				{
					if(i%2==1)
					{
							if(a[i+2]=='3')
							{
								if(k%2==1)
									a[i+1]='2';
								k=0;
								break;
							}
							a[i+1]='2';
							--k;
					}
					else//i%2==0
					{
							if(i>1&&a[i-1]=='2')
							{
								if(k%2==1)
									a[i]='3';
								k=0;
								break;
							}
							a[i]='3';
							--k;
					}
				}
			}
		for(int i=1;i<=n;++i)
			printf("%c",a[i]);
		printf("\n");
	}
	return 0;
}

