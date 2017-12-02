#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char a[10001][100];
int main()
{
	//freopen("biology.in","r",stdin);
	//freopen("biology.out","w",stdout);
	int n,m,g1,g2,g3,g4,g5,max;
	cin>>n>>m;
	g2=n;
	for(int i=1;i<=n;i++)
	gets(a[i]);
	for(int i=1;i<=m;i++)
	{
     	scanf("%d",&g1);
	if (g1==1) gets(a[g2++]);
	else
	{
	 scanf("%d%d%d",&g3,&g4,&g5);
	 int l1,l2;
l1=strlen(a[g4]);l2=strlen(a[g5]);
     for(int i=1;i<=l1;i++)
     for(int k=1;k<=l2;k++)
     {
     	int h1=k;int z=0; int max;
       while(a[g3][i]==a[g4][h1]){ h1++;z++;if (z>max) max=z;}  
   }
    for(int i=1;i<=l2;i++)
     for(int k=1;k<=11;k++)
     {
     	int h1=k;int z=0; 
       while(a[g4][i]==a[g3][h1]){ h1++;z++;if (z>max) max=z;}  
   }
	
	cout<<max<<endl;
	}

	}
	return 0;
}

