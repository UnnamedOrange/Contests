#include<bits/stdc++.h>
using namespace std;
char st[1000100];
int main()
{
	srand(time(NULL));
	int n,m;long long k;scanf("%d%d%lld",&n,&m,&k);cout<<n<<' '<<m<<' '<<k<<endl;
	for (int i=1;i<=n;i++)
	{
		if (rand()%(n)) st[i]='?';else st[i]='a'+rand()%26;
		putchar(st[i]);
	}
	putchar('\n');
	while (m--)
	{
		int l=rand()%n+1,r=rand()%n+1;
		if (l>r) swap(l,r);
		cout<<l<<' '<<r<<endl;
	}
}
