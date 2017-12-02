#include<cstdio>
#include<cstring>
#include<iostream>
const int size=1024;
using namespace std;
int n;
int f[size];
long long ans;
bool v[10];
int u[10]={1,2,4,8,16,32,64,128,256,512};
int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%d",&n);
	int a,b;
	for(int i=1;i<=n;i++){
		a=i,b=0;
		memset(v,0,sizeof(v));
		while(a) v[a%10]=1,a/=10;
		for(int j=0;j<=9;j++) if(v[j]) b+=u[j];
		f[b]++;
	}
	for(int i=0;i<size;i++) ans+=1ll*f[i]*(f[i]-1)/2;
	cout<<ans<<endl;
	return 0;
}
