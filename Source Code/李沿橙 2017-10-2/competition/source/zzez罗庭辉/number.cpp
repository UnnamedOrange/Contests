#include <bits/stdc++.h>
using namespace std;
typedef long long lol;
struct cmp{lol a[10];lol num;}e[10000000];
lol n,ans;
inline void get(lol nbe){
	int id=nbe;
	while(nbe){
		e[id].a[nbe%10]=1;
		nbe=nbe/10;	}
	for(lol i=0;i<=9;i++)
	e[id].num+=e[id].a[i];
	}
inline void judge(lol x,lol y){
	lol sum=0;
	bool flag=1;
	for(int k=0;k<=9;k++)
	if(e[x].a[k]==e[y].a[k]) sum++; 
	else {flag=0;break;}
	if(sum==10&&flag==1) ans++;
}	
int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	cin>>n;
	for(lol i=1;i<=n;i++)
	get(i);
	for(lol i=1;i<n;i++)
		for(lol j=i+1;j<=n;j++)
	{if(e[i].num==e[j].num) judge(i,j);
	else continue;	}
	cout<<ans<<endl;
	return 0;
}
