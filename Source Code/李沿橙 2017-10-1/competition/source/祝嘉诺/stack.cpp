#include<bits/stdc++.h>
using namespace std;
int n;
long long sum;
void dfs(int _in,int _out,int _print)
{
	if(_print==n) 
	{
		sum++;return;
	}
	if(_out==0) dfs(_in,_out,_print+1);//数全部在栈内则pop()； 
	else if(_in==0) dfs(_in+1,_out-1,_print);//栈空且out不为0则push();
	else
	{
		dfs(_in+1,_out-1,_print);//push();
		dfs(_in-1,_out,_print+1);//pop();
	}
	return; 
}
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	int in,out,print;
	cin>>n;
	in=0;out=n;print=0;
	dfs(in,out,print);
	cout<<sum%7;
}
