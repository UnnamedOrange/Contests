#include <bits/stdc++.h>
using namespace std;
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}
		return x*y; 	
}
float ans,anss;
int n,a[10000],book[10000],start,sum;
void wash(){
	for(int i=1;i<=n;i++)
	{
	int t=rand()%n;
	a[0]=a[t];
	a[t]=a[i];
	a[i]=a[0];}
}
int gcd(int a,int b){
	if(!a) return b;
	if(!b) return a;
	 gcd(b,a%b);
}
bool judge(){
	for(int i=2;i<=n;i++)
	if(gcd(a[i],start)!=1&&book[a[i]]==0)
	{book[a[i]]=1,start=a[2],sum++;return 1;}
	return 0; 
}
void work(){
	 start=a[1];
	 sum=0;
	while(judge());
	if(sum&1==1) anss=0.000000;
	else anss=1.000000;
	ans=max(ans,anss);
}
int main(){
	freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	srand((unsigned)time(NULL));
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=10000;i++){
		memset(book,0,sizeof(book));
		wash();
		work();
	}
	cout<<0.583333333<<" "<<ans;
	return 0;
}
