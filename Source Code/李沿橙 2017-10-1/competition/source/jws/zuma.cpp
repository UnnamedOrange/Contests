#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MAXL 405
int len,ans=0;
int a[MAXL];
using namespace std;
int main()
{
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	char ch='0';
	while(ch=='0' || ch=='1')
	{
		scanf("%c",&ch);
		len++;
		a[len]=ch-'0';
	}
	len--;
	for(int i=1;i<=len-1;i++)
	{
		if(a[1]==-1 && a[len]==-1) break;
		if(a[i]==a[i+1])
		{
			a[i]=-1;
			a[i+1]=-1;
			int l=i-1,r=i+2;
			if(l<=0 || r>len) continue;
			while((l-1>=1 && a[l-1]==a[l]) || (r+1<=len && a[r+1]==a[r]))
			{
				if(a[l-1]==a[l] && a[r+1]==a[r])
				{
					a[l]=-1;
					a[l-1]=-1;
					a[r]=-1;
					a[r+1]=-1;
					l-=2;
					r-=2;
				}
				else if(l-1>=1 && a[l-1]==a[l])
				{
					a[l]=-1;
					a[l-1]=-1;
					a[r]=-1;
					l-=2;
					r++;
				}
				else if(r+1<=len && a[r+1]==a[r])
				{
					a[l]=-1;
					a[r]=-1;
					a[r+1]=-1;
					l--;
					r+=2;
				}
			}
			ans++;
		}
	}
	if(ans==0) printf("1\n");
	else printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
