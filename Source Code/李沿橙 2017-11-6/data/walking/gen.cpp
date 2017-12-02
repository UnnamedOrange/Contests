#include<bits/stdc++.h>
using namespace std;
int ran()
{
	while (1)
	{
		int ans=rand();
		if ((ans==0)||(ans>1000000000)) continue;
		return ans;
	}
}
int fa[1000100],rd[1000100];
int main()
{
	srand(time(NULL));
	int n;scanf("%d",&n);printf("%d\n",n);
	for (int i=1;i<=n;i++) printf("%d ",ran());printf("\n");
	for (int i=2;i<=n;i++)
	{
		if (i<=50) fa[i]=rand()%(i-1)+1;
		else if (rand()%5) fa[i]=i-1-rand()%10;
		else fa[i]=i-1-rand()%50;
	}
	for (int i=1;i<=n;i++) {rd[i]=i;swap(rd[i],rd[rand()%i+1]);}
	for (int i=2;i<=n;i++) printf("%d %d\n",rd[i],rd[fa[i]]);
}
