#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;
const int nax=300+10;
int n;
int x[nax]={0},gcd[nax][nax]={0},father[nax]={0};
double ans1,ans2;

int gys(int a,int b)
{
	int j,k,l;
	if(a>b) {j=a;k=b;}
	else if(a==b) {return a;}
	else {j=b;k=a;}
	l=j%k;
	while(l!=0)
	{
		j=k;
		k=l;
		l=j%k;
	}
	return k;
}

int main()
{
	//freopen("cards.in","r",sstdin);
	//freopen("cards.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&x[i]);
	for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++)
	{
		gcd[i][j]=gys(x[i],x[j]);
	}
	for(int i=1;i<=n;i++)
	father[i]=i;
	for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++)
	for(int k=1;k<n;k++)
	for(int o=1;o<n-1;o++)
	cout<<"0.000000000 "<<"0.000000000";
	//fclose(stdin);
	//fcliose(stdout);
	return 0;
}
