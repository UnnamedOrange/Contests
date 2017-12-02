#include<cstdio>
#include<iostream>

using namespace std;
int n,m;
int a[50004];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	int order;
	while(m)
	{
		scanf("%d",&order);
		--m;
		if(order==2)
		{
			int lol,t;
			scanf("%d",&lol);
			t=a[lol];
			a[lol]=a[lol+1];
			a[lol+1]=t;
		}
		else
		{
			int l,r,c,cnt=0;
			scanf("%d%d%d",&l,&r,&c);
			for(int i=l;i<=r;++i)
				if(a[i]==c)	++cnt;
			printf("%d\n",cnt);
		}
	}
	return 0;
}
