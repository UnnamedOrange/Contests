#include<bits/stdc++.h>
using namespace std;
#define N 100000+5
char a[N];
int seg_a[N],t,k,begin,n,book;
int foundx(int x)
{
	int i;
	for(i=x;i<=n;i++)
	{
		if(seg_a[i]==2&&seg_a[i+1]==3)
		{
			return i;
		}
	}
	return i;
}
int main()
{
	int len,find,p;
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(cin>>n>>k)
	{
		t=0;
		getchar();
		gets(a);
		for(int i=0;i<n;i++)
		{
			seg_a[i+1]=a[i]-'0';
		}
		int i;
		for(i=1;i<=k;i++)
		{
			p=0;
			find=foundx(t);
			if(find==n) break;
			if(find%2==0)
			{
				p=3;
				seg_a[find]=3;
			}
			else
			{
				p=2;
				seg_a[find+1]=2;
			}
			if(p==3) t=find-1;
			if(p==2) t=find;
		}
		for(int i=1;i<=n;i++)
		{
			cout<<seg_a[i];
		}
		cout<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
