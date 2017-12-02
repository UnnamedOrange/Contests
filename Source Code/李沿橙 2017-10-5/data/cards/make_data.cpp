#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<string>
#include<ctime>
#include<cmath>
#include<algorithm>
#define INF 1111111111
#define N 111111
#define eps 1e-9
using namespace std;
char name[22]; 
int tot=0,n=300,k=1000;
int a[N];
void pre()
{
	for (int i=1;i<=k;i++)
	{
		int t=i;
		while (t%2==0) t/=2;
		while (t%3==0) t/=3;
		while (t%5==0) t/=5;
		while (t%7==0) t/=7;
		while (t%11==0) t/=11;
		while (t%13==0) t/=13;
		while (t%17==0) t/=17;
		while (t%19==0) t/=19;
		if (t==1) a[++tot]=i;	
	}
	return ;
}
int main()
{
	srand(time(0));
	pre();
	for (int i=9;i<=10;i++)
	{
		sprintf(name,"geme%d.in",i);
		freopen(name,"w",stdout);
		printf("%d\n",n);
		for (int j=1;j<=n;j++) printf("%d ",a[rand()%tot+1]);
		fclose(stdout);
	} 
	return 0;
}
