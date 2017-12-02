#include<iostream>
#include<cstdio>
using namespace std;
int pu=0,po=0;
int search(int);
int n,n2;
int tim=0;
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	cin>>n;
	n2=n*2;
	search(1);
	cout<<tim;
	return 0;
}
int search(int pl)
{
	if(pu>0)//pop
	{
		pu--;
		if(pl==n2)
		if(pu==0)
		{
		tim++;
		if(tim>6)
		tim-=7;
		}
		if(pl<n2)
		search(pl+1);
	}
	if(pl<n2)//push
	{
		pu++;
		search(pl+1);
	}
}
