#include <bits/stdc++.h>
using namespace std;
int n,a[2000];
string s;
int main(){
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	cin>>s;
	int n=s.size();
	if(n==1) {cout<<2<<endl; return 0;}
	if(n%2==1)cout<<2<<endl;
	else cout<<3<<endl;
	return 0;	
}
