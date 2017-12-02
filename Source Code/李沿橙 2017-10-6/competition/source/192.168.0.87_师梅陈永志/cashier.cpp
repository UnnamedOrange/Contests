#include<bits/stdc++.h>
using namespace std;
#define N 24+5
#define T 10+5 
int a[N],b[N],book[T];
int main()
{
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	int t;
	cin>>t;
	for(int kl=0;kl<t;kl++)
	{
		for(int i=0;i<=23;i++)
			cin>>a[i];
		for(int i=0;i<=23;i++)
			cin>>b[i];
		for(int i=0;i<=23;i++)
		{
			if(a[i]!=0)
			{
				int j=i;
				for(int op=7;op>=0;op--)
				{
					if(b[j]!=0)
					{
						while(a[i]!=0&&b[j]!=0)
						{
							b[j]--;
							int k=j;
							for(int op2=7;op2>=0;op2--)
							{
								if(a[k]!=0) a[k]--;
								k++;
								if(k>=24) k=24-k;
							}
							book[kl]++;
						}
					}
					if(a[i]==0) break;
					j--;
					if(j<0) j=24+j;
				}	
				if(a[i]!=0)
				{
					book[kl]=-1;
					break;
				}
			}
		}
	}
	for(int i=0;i<t;i++)
	{
		cout<<book[i]<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
