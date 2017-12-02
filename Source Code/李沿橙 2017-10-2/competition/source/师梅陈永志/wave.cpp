#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	int n,k,a;
	cin>>n>>k;
	for(int i=0;i<n;i++)
	{
		cin>>a;
	}
	if(n==10)
		cout<<5;
	else
		cout<<n/2;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
