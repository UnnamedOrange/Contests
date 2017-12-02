#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;
const int l=10+1;
char n[l];
int k[l];
unsigned long long ans=0;

inline int zh(int t)
{
	return t*(t-1)/2;
}

inline int px1(int t)
{
	for(int i=l;i>=1;i--)
	{
		if(k[i]>t) break;
		else if(k[i]<t) return 0;
	}
	return 1;
}

int main()
{
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%c",n);
	d=strlen(n);
	for(int i=0;i<d;i++)
	k[i+1]=n[i]-'0';
	for(int i=1;i<=9;i++)
	{
		if(px1(i))
		ans+=zh(l);
		else
		ans+=zh(l-1);
		
	}
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
