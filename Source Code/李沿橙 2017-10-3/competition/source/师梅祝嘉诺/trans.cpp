#include<bits/stdc++.h>
using namespace std;
char a[1000001]; 
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	int n,k;
	int x,t;
	//scanf("%d%d",&n,&k) != EOF
	while(cin>>n>>k)
	{
		//cin>>n>>k;
		getchar();
		gets(a);
		t=-1;
		int flag=0;
		for(int j=1;j<=k;j++)
		{
			x=-1;
			for(int i=0;i<n-1;i++)
			{
				if(a[i]=='2' && a[i+1]=='3' )
				{
					x=i;
					break;
				}
			}
			if(x==-1)
			{
				flag=1;
				printf("%s\n",a);
				break;
			}
			if((x+1)%2==1) a[x+1]='2';
			else a[x]='3';
		}
		if(flag==0) printf("%s\n",a);
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
