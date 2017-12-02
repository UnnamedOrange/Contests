#include<iostream>
#include<cstdlib>

using namespace std;
const int len=100000+10;
int n,m,l;
unsigned long long x,y;

int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w"),stdout;
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>x;
	for(int i=1;i<=n;i++)
	cin>>y;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		l=n%m+y-x;
		if(l)
		cout<<"0"<<endl;
		else
		cout<<n<<endl;
	}
	fclose(stdin);
	fclose(sdtout);
	return 0;
}
