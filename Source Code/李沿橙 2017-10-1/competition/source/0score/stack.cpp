#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
int n;
int a[1005];
bool b[1005];
stack<int>st;
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)a[i]=i;
	int ans=0;
	do
	{
		int mk=0;bool f=0;
		for(int i=1;i<=n;++i)
		{
			if(mk<a[i])
			{
				b[a[i]]=1;
			}
			else
			{
				b[a[i]]=0;
			}
			mk=max(mk,a[i]);
		}
		int to=0;
		for(int i=1;i<=n;++i)
		{
			if(!b[i])st.push(i);
			if(b[i])
			{	
				to++;
				while(!st.empty()&&a[to+1]==st.top()){to++;st.pop();}
			}
		}
		if(st.empty())ans++;
		while(!st.empty())st.pop();
	}while(next_permutation(a+1,a+1+n));
	cout<<ans<<endl;
	return 0;
}
