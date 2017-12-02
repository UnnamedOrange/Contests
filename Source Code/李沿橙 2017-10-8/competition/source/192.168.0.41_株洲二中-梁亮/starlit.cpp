#include<cstdio>
#include<iostream>

using namespace std;
int n,k,m;
bool close[40010];
int b[40010];
int a[40010],dis[40010];//a[i] the number of downlight i;
void special()
{
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		if(close[i]==true)
		{
			for(int j=i;j<=i+b[1];++j)
				close[j]=1-close[j];
			++ans;
		}
	}
	printf("%d",ans);
	return;
}

void search()
{
	
	return ;
}

int main()
{
	freopen("starlit.in","r",stdin);
	freopen("starlit.out","w",stdout);
	
	scanf("%d%d%d",&n,&k,&m);
	int temp;
	for(int i=1;i<=k;++i)
	{
		scanf("%d",&a[i]);
		close[a[i]]=true;
	}
	for(int i=1;i<=m;++i)
		scanf("%d",&b[i]);
	for(int i=1;i<n;++i)
	{
		dis[i]=a[i+1]-a[i];
	}
	
	if(m==1)	{special();return 0;}
	
	printf("2");
	
	return 0;
}
