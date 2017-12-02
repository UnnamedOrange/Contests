#include<algorithm>
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
const int N=100005;
int a[N];
string s[N];
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	int n,m,x,t,len;			
	scanf("%d%d",&n,&m);	
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=m;i++) 
	{
		cin>>x;
		if(x==1) cin>>s[++n];
		if(x==2)
		{
			len=100;
			cin>>t;
			for(int j=1;j<=t;j++) cin>>a[j];
			for(int k=1;k<=t;k++)			
			{	
				for(int j=1;j<=t;j++)
				{
					x=0;
					if(j==k) continue;
					while(s[a[j]][s[a[j]].length()-x-1]==s[a[k]][s[a[k]].length()-x-1]) x++;
					len=min(x,len);
				}
			}
			cout<<len<<endl;	
		}
	}	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
