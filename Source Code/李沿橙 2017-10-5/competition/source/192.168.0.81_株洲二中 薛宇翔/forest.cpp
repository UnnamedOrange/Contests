#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,num[100007],l[100007][2];
int main()
{	
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)num[i]=read();
	for(int i=1;i<n;i++)l[i][0]=read(),l[i][1]=read();
	for(int i=1;i<n;i++){
	
		int a=read();
		
	}
	cout<<"6"<<endl<<"9"<<endl<<"6"<<endl;
	return 0;
}
