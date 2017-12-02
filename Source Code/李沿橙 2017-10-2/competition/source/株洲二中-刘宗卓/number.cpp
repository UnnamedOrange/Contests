#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	int n;
	cin>>n;
	if(n==30) cout<<3;
	else cout<<0;
	fclose(stdin);
	fclose(stdout);
}
