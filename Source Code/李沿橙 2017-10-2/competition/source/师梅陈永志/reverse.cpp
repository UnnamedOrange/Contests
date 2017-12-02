#include<bits/stdc++.h>
using namespace std;
#define N 10000+5
char p[N];
int a[N],len,s;
int foundzero(int i)
{
	int k=i;
	if(i==len) 
		return i-k;
	while(a[i]==0)
	{
		i++;
		if(i==len) 
			return i-k;
	}
	return i-k;
}
void reverse(int one,int i)
{
	
	int k=0;
//	cout<<1<<" "<<s<<" "<<one<<" "<<i<<endl;
	if(i==len) return ;
	if(a[i]==0) 
	{
		return reverse(one,i+1);
	}
	if(a[i]==1)
	{
		if(a[i+1]==0)
		{
			k=foundzero(i+1);
			if(k>one)
				s+=(++one); 
			else s+=k;
//			cout<<s<<" "<<one<<" "<<k<<endl;
			reverse(0,i+k+1);
		}
		else 
			reverse(one+1,i+1);
	}
	return ;
}

int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int k,t;
	gets(p);
	len=strlen(p);
	for(int i=0;i<len;i++)
	{
		if(p[i]=='1') a[i]=1;
	}
	reverse(0,0);
	cout<<s;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
