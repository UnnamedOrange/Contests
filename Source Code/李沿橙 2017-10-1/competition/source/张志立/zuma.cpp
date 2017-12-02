#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
string a;
int l;
int main()
{
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	cin>>a;
	l=a.size();
	if(l>5)
	cout<<6;
	if(l==1) cout<<2;

	if(l==2)
	{
	if(a[0]==a[1]) cout<<1;
	else cout<<4;
	}
	if(l==3) cout<<3;
	
	if(l==4)				
	{
		if(a[0]==a[1]||a[1]==a[2]||a[2]==a[3]) cout<<2;
		else cout<<5;
	
	}
	if(l==5) cout<<4;
	return 0;
}
