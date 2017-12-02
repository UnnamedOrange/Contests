#include<cstdio>
using namespace std;
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	int n,k,a,x,y,z;
	scanf("%d%d",&n,&k);
	scanf("%d",&x);
	y=1;
	z=1;
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&a);
		if(y==1)
		{
			if(a-x>=k)
			{
				z++;
				y^=1;
				x=a;
			}
			else if(a<x)
			x=a;
		}
		else 
		{
			if(x-a>=k)
			{
				z++;
				y^=1;
				x=a;
			}
			else if(a>x)
			x=a;
		}
	}
	printf("%d\n",z);
	return 0;
}
	
			
		
