#include<iostream>
#include<cstdio>
#include<cstring>

#define N 30007

using namespace std;
int n,m,ans,cnt;
int fa[N],val[N];
char ch;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}

inline int find(int x)
{
	if(x==fa[x]) return x;
	else return fa[x]=find(fa[x]);
}

void merge(int x,int y)
{
	int r1=find(x),r2=find(y);
	if(r1==r2) return;
	for(int i=1;i<=n;i++) 
	  if(find(i)==r1) val[i]+=val[r2];
	fa[r2]=r1;
}


int main()
{
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
	n=read();int x,y;
	for(int i=1;i<=n;i++) fa[i]=i,val[i]=1;
	for(int i=1;i<=n;i++)
	{
		cin>>ch;
		if(ch=='M')
		{
			x=read();y=read();
			merge(x,y);
		}
		if(ch=='C') x=read(),printf("%d\n",val[x]-1);
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
