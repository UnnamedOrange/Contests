#include<bits/stdc++.h>
using namespace std;
int num[10]={1024,1,2,4,8,16,32,64,128,256};
int n;
bool book[10];
int lala(int x)
{
	memset(book,0,sizeof book);
	int t=x,wei=1,la,sum=0;
	for(int i=10;;i*=10)
	{
		if(x>=i) wei++;
		else break;
	}
	for(int i=1;i<=wei;i++)
	{
		int la=t%10;
		book[la]=1;
		t/=10;
	}
	for(int i=0;i<=9;i++)
	{
		if(book[i]==1) sum+=num[i];
	}
	return sum;
}
int main()
{
	int sum=0;
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n;
	char* la;
	int t1,t2;
	for(int i=1;i<=n;i++)
	{
		t1=lala(i);
		for(int j=i+1;j<=n;j++)
		{
			t2=lala(j);
			if(t1==t2) sum++;
		}
	}
	cout<<sum;
	//fclose(stdin);fclose(stdout);
	return 0;
}
