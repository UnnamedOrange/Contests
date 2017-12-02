#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,y=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')y=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*y;
}
int n,m,k=0;
int num[300005];
struct a{
	int color,top,val,hand,next;
}e[300005];
void add(int ax,int ay)
{
	k++;
	e[k].color=ax;e[k].top=ay;e[k].val=e[e[ax].hand].val+1;
	e[k].next=e[ax].hand;e[ax].hand=k;
}
void doit(int x,int y,int z)
{
	int clo=e[z].hand,xi=e[clo].val,yi=e[clo].val;
	while(x<=e[clo].top){
		clo=e[clo].next;
		xi=e[clo].val;
		//if(!clo)break;
	}
	clo=e[z].hand;
	while(y<e[clo].top){
		clo=e[clo].next;
		yi=e[clo].val;
		//if(!clo)break;
	}	
	//cout<<xi<<" "<<yi<<endl;
	cout<<yi-xi<<endl;
}
void wr(int ccc,int rrr)
{	int cl1=num[ccc],cl2=num[rrr];
	cl1=e[cl1].hand;cl2=e[cl2].hand;
	while(!cl1){
		if(e[cl1].top>=ccc)e[cl1].val--;
		cl1=e[cl1].next;
	}
	while(!cl2){
		if(e[cl2].top>=rrr)e[cl2].val--;
		cl2=e[cl2].next;
	}
	cl1=num[ccc],cl2=num[rrr];
	cl1=e[num[ccc]].hand;cl2=e[num[rrr]].hand;
	while(!cl1){
		if(e[cl1].top>=rrr)e[cl1].val++;
		cl1=e[cl1].next;
	}
	while(!cl2){
		if(e[cl2].top>=ccc)e[cl2].val++;
		cl2=e[cl2].next;
	}
	
}
int main()
{	
	/*freopen("color.in","r",stdin);
	freopen("color.out","r",stdout);*/
	n=read();m=read();
	e[0].color=e[0].hand=e[0].next=e[0].top=e[0].val=0;
	for(int i=1;i<=n;i++)num[i]=read(),add(num[i],i);
	/*for(int i=1;i<=n;i++){
		cout<<e[i].color<<" "<<e[i].hand<<" "<<
		e[i].next<<" "<<e[i].top<<" "<<e[i].val<<endl;
	}*/
	for(int i=1;i<=m;i++){
		int a,b,c,d;
		a=read();b=read();if(a==1)c=read(),d=read();
		if(a==2)wr(b,b+1);
		if(a==1)doit(b,c,d);
	}
	return 0;
}
