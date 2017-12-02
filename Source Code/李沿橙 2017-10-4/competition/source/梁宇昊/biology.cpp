#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;

int n,m;
bool book[21000];
string s[21000];

inline int pd(string a,string& b)
{
	string c;//,k;
	if(a.size()<b.size())	swap(a,b);
	int tot=0;
	//cout<<"a="<<a<<endl;
	for(register int l=0,r=b.size()-1;l<b.size();++l)
		{
			c="";
			for(register int i=l;i<=r;++i)
				c=c+b[i];
			//cout<<"c="<<c<<endl;
			if(a.find(c)==a.size()-c.size() && tot<c.size())
			{
				///printf("RE");
				//cout<<"c="<<c<<endl;
				//cout<<"c.size()="<<c.size()<<endl;
				tot=c.size();
			//	for(register int len=0;len<c.size();++len)
				//	k=k+c[len];
			}
		}
	//for(register int len=0;len<b.size();++len)
		//b+=k[len];
	//cout<<b;
	return tot;
}

int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;++i)
		std::cin>>s[i];//cout<<s[i]<<endl;
	for(register int i=1;i<=m;++i)
	{
		int a;
		scanf("%d",&a);
		if(a==1)
			std::cin>>s[++n];
		else
		{
			string c="";
			int t,b,tot=123456789;
			scanf("%d",&t);
			memset(book,0,sizeof(book));
			for(register int j=1;j<=t;++j)
			{
				scanf("%d",&b);
				if(book[b]) continue;
				book[b]=1;
				if(j==1)
					for(register int len=0;len<s[b].size();++len)
						c=c+(char)s[b][len];
				else
					tot=min(tot,pd(s[b],c));
			}
			if(tot==123456789)	tot=min((int)tot,(int)c.size());
			printf("%d\n",tot);
		}
	}
	return 0;
}
