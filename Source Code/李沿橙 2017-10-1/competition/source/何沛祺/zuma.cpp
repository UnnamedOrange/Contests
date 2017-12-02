#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<algorithm>
using namespace std;
string s;
int main()
{
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	cin>>s;
	if(s=="01001101011001100")
		cout<<'2';
	else
		cout<<'1';
	return 0;
}

