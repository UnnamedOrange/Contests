#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define rint register int
using namespace std;
int n,m;
string s[21000];
bool book[21000];
inline int pd(string a,string& b)
{
	string c;
	if(a.size()<b.size())	swap(a,b);
	int tot=0;
	for(rint l=0,r=b.size()-1;l<b.size();++l){
			c="";
		for(rint i=l;i<=r;++i)	c=c+b[i];
		if(a.find(c)==a.size()-c.size() && tot<c.size()){tot=c.size();}
		}
	return tot;
}
int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(rint i=1;i<=n;++i)	cin>>s[i];
	for(register int i=1;i<=m;++i){
		int a;
		scanf("%d",&a);
		if(a==1)	cin>>s[++n];
		else{
			string c="";
			int t,b,tot=999999999;
			scanf("%d",&t);
			memset(book,0,sizeof(book));
			for(rint j=1;j<=t;++j){
				scanf("%d",&b);
				if(book[b]) 	continue;
				book[b]=1;
				if(j==1)	for(register int len=0;len<s[b].size();++len)	c=c+(char)s[b][len];
				else	tot=min(tot,pd(s[b],c));
			}
			if(tot==999999999)	tot=min((int)tot,(int)c.size());
			printf("%d\n",tot);
		}
	}
	return 0;
}
