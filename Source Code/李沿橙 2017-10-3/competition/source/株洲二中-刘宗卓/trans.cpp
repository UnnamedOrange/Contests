#include <iostream>
#include <cstdio>
using namespace std;
int num[1000001]={0};
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	int t=0,temp;
	 int n,k;
	 cin>>n>>k;
	 for(int i=1;i<=n;i++)	cin>>num[i];
	 temp=num[1];
	 	for(int i=1;i<=k;i++)
	 	{
	 		for(int j=1;j<=n;j++)
	 			if(num[i]<temp) temp=num[i];	//找最小值，如果没有找第一个点 
				 else t=1;
				 
				 if(t!=1) 				
	 			{
	 					for(int a=1;a<=n;a++)
	 				if(temp==num[a])
	 				{
	 				t=a;							//标记 
	 				break;
	 				}
	 			}
						num[t]=2;
						num[t+1]=3;
					if(t%2==1)
						num[t+1]=2;	
	 			else if(t%2==0)
	 			
	 				num[t]=3;
	 				
	 			
	 	}
	 	for(int i=1;i<=n;i++)	cout<<num[i];
	fclose(stdin);
	fclose(stdout);
	return 0;
}
