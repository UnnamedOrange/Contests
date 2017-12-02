#include <bits/stdc++.h>
using namespace std;
typedef long long lol;
lol t,a[25],b[25],a1[25],b1[25],ans,ans1,ans2;
int read(){
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') y=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';c=getchar();}
		return x*y;	
}
void tan1(int id,int idd){
	int sd;
	while(b[id]&&a[idd]){
	for(int i=0;i<=7;i++){
		sd=id+i;
		if(id+i>23) sd=id+i-24; 
		if(a[sd]!=0) a[sd]=a[sd]-1;}
	//for(int j=0;j<24;j++) cout<<a[j]<<" ";
	//cout<<endl;  		
	ans1++;b[id]--;}
}
void work1(int id){
	int i=0,idd=id,sd,sum=0;
	while(i<=7)
	{
	sd=id-i;	
	if(id-i<0) sd=id-i+24;	
	sum+=b[sd];
	i++;}
	if(sum<a[id]) ans1=-1;
	else {
	i=0;
	while(a[id]&&i<=7)
	{
	sd=id-i;	
	if(id-i<0) sd=id-i+24;	
	if(b[sd]!=0) tan1(sd,idd);
	i++;}}
}
void tan2(int id,int idd){
	int sd;
	while(b[id]&&a[idd]){
	for(int i=0;i<=7;i++){
		sd=id+i;
		if(id+i>23) sd=id+i-24; 
		if(a[sd]!=0) a[sd]=a[sd]-1;}
	//for(int j=0;j<24;j++) cout<<a[j]<<" ";
	//cout<<endl;  		
	ans2++;b[id]--;}
}
void work2(int id){
	int i=0,idd=id,sd,sum=0;
	while(i<=7)
	{
	sd=id-i;	
	if(id-i<0) sd=id-i+24;	
	sum+=b[sd];
	i++;}
	if(sum<a[id]) ans2=-1;
	else {
	i=0;
	while(a[id]&&i<=7)
	{
	sd=id-i;	
	if(id-i<0) sd=id-i+24;	
	if(b[sd]!=0) tan2(sd,idd);
	i++;}}
}

int main(){
	freopen("cashier.in","r",stdin);
	freopen("cashier.out","w",stdout);
	t=read();
	for(int i=1;i<=t;i++){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		ans=0; ans1=0;ans2=0;
	for(int i=0;i<24;i++) a1[i]=a[i]=read();
	for(int i=0;i<24;i++) b1[i]=b[i]=read();
	for(int i=0;i<24;i++)
	{if(a[i]!=0) work1(i);
	if(ans1==-1)break;}
	for(int i=0;i<24;i++)
	{b[i]=b1[i];a[i]=a1[i];}
	for(int i=23;i>=0;i--)
	{if(a[i]!=0) work2(i);
	if(ans2==-1)break;}
	ans=min(ans1,ans2);
	cout<<ans<<endl;}
	return 0;
}
