#include<bits/stdc++.h>
using namespace std;
long long ran()
{
	if (rand()%5==0) return 0;
	if (rand()%5==0) return 1;
	return (long long)rand()*rand()+rand();
}
int main()
{
	srand(time(NULL));
	int t=50;printf("%d\n",t);
	long long mx;cin>>mx;
	while (t--)
	{
		printf("%lld %lld\n",ran()%mx+1,ran()%mx+1);
	}
}
