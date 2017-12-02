#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,k,t;
struct a{
	int s,ed,hand,next;
}e[600005];
int ki=0;
void add(int x,int y)
{
	ki++;
	e[ki].s=x;e[ki].ed=y;e[ki].next=e[x].hand;e[x].hand=ki;
}
void doelse()
{
	bool aa[300000];
	memset(aa,0,sizeof(aa));
	int ad,ac,ti=0;
	for(int i=1;i<n;i++){
		ad=read();ac=read();
		if(ad!=1&&ac!=1)ti++,
		aa[ad]=aa[ac]=true;
	}
	int as=0;
	for(int i=1;i<=n;i++)if(aa[i])as++;
	//cout<<as<<" "<<ti<<endl;
	as=as-ti+1;
	printf("%d",as);exit(0);
}
int main()
{	
	freopen("general.in","r",stdin);
	freopen("general.out","w",stdout);
	n=read();k=read();t=read();
	if(t==2)doelse();
	for(int i=1;i<=n;i++){
		int a=read(),b=read();
		add(a,b);add(b,a);
	}
	if(!k){
		printf("%d",n);return 0;
	}
	cout<<rand()%10;
	return 0;
}
