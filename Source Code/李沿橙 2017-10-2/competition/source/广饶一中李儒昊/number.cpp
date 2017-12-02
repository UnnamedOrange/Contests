#include<iostream>
#include<cstdio>
#include<cstring>

#define size 1024

using namespace std;
int n,cnt[size],vis[10];
int Use[10]={1,2,4,8,16,32,64,128,256,512};
long long ans;

int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	cin>>n;
	int start,End;
	for(int i=1;i<=n;i++)
	{
		start=i;End=0;memset(vis,0,sizeof vis);
		while(start) vis[start%10]=1,start/=10;
		for(int j=0;j<=9;j++) if(vis[j]) End+=Use[j];
		cnt[End]++;
	}
	for(int i=0;i<size;i++) ans+=1ll*cnt[i]*(cnt[i]-1)/2;
	cout<<ans<<endl;
	fclose(stdin);fclose(stdout);
	return 0;
}
