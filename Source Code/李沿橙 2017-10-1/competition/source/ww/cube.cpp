#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
#include<cstdio>

using namespace std;

const int N=30005;
int sum,getS[N],getF[N];
int findF(int);
int findS(int);
int main()         
{
   freopen("cube.in","r",stdin);
   freopen("cube.out","w",stdout);
	int p,a,b,x,y;
	char k;
 	cin>>p;
	for(int i=1;i<=N;i++) getS[i]=getF[i]=i;
	for(int i=1;i<=p;i++)
	{
		cin>>k;
		if(k=='M')	
		{
			cin>>a>>b;
			x=findS(a),y=findF(b);
			//cout<<x<<" "<<y<<endl;
			getF[y]=getS[x];  			
			getS[x]=y;
		}
		else
		{
			sum=0;
			cin>>a;
			findS(a);
			printf("%d\n",sum-1);
		}
	}
	//cout<<endl;
	//for(int i=1;i<=p;i++) sum=0,findS(i),cout<<sum-1<<endl;
   fclose(stdin);
   fclose(stdout);
   return 0;
}

int findS(int x)
{
	sum++;
	return x==getS[x]?x:findS(getS[x]);
}
int findF(int x)
{
	return x==getF[x]?x:findF(getF[x]);
}
