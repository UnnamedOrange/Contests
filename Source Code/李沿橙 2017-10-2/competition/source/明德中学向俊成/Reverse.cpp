#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
char a[10010];
int b[10010];
int main()
{
	freopen("Reverse.in","r",stdin);freopen("Reverse.out","w",stdout);
	int i,j,k,m,n;
	gets(a);
	int la;
	la=strlen(a);
	int t,jl,s=1;
	t=jl=a[0]-'0';
	j=1;
	for(i=1;i<la;i++)
	{
		if(a[i]-'0'!=t)
		{
			b[j]=s;
			t=a[i]-'0';
			s=1;
			j++;
		}
		else s++;
	}
	if(a[la-1]-'0'!=t)
	{
		b[j]=1;
	}
	else if(a[la-1]-'0'==t)b[j]=s;
	int count=0,head,tail;
	tail=j;
	head=1;
	int js=0;
	if(jl==1)
	{
		for(i=head+1;i<=tail;i+=2)
		{
			js+=b[i];
		}
		if(js>b[1])
		{
			jl=0;
			head++;
			count+=b[1];
		}
		else
		{
			count+=js;
			printf("%d\n",count);
			return 0;
		}
	}
	else if(jl==0&&tail%2==1)
	{
		js=0;
		for(i=head;i<=tail;i+=2)
		{
			js+=b[i];
		}
		if(js>b[tail])
		{
			tail--;
			count+=b[tail+1];
		}
		else 
		{
			count+=js;
			printf("%d\n",count);
			return 0;
		}
	}
	int mid=(head+tail)/2,s1=0,s2=0;
	if(mid%2==1)
	{
		for(i=head+1;i<mid;i+=2)
		{
			s1+=b[i];
		}
		for(i=mid;i<=tail;i+=2)
		{
			s2+=b[i];
		}
		if(s1>s2)
		count+=s2;
		else count+=s1;
	}
	else
	{
		for(i=head+1;i<=mid;i+=2)
		{
			s1+=b[i];
		}
		for(i=mid+1;i<=tail;i+=2)
		{
			s2+=b[i];
		}
		if(s1>s2)
		count+=s2;
		else count+=s1;
	}
	printf("%d\n",count);
	return 0;
}
