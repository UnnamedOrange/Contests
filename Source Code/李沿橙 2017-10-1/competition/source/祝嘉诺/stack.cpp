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
	if(_out==0) dfs(_in,_out,_print+1);//��ȫ����ջ����pop()�� 
	else if(_in==0) dfs(_in+1,_out-1,_print);//ջ����out��Ϊ0��push();
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
