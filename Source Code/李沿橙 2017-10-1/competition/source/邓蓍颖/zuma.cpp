#include<bits/stdc++.h>
using namespace std;
char c[660];long long ans=99999999,len,co[1000000],tot,l,n,r;
int find(int x)
{
	l=x-1,r=x+1;
	tot=0;
	if(co[x]!=-1)tot++;
	while(co[x]==-1&&x>1)x--;
	if(x&&co[x]!=-1)
	{
		while(co[l]==co[x]||co[l]==-1)
		{
			if(l==0)break;
			if(co[l]==co[x])tot++;
			l--;
			if(l==0)break;
		}
	}
	if(co[x]==-1||!x)while(co[x]==-1&&x<len)x++;
	while(co[r]==co[x]||co[r]==-1)
	{
		if(r==len+1)break;
		if(co[r]==co[x])tot++;
		r++;
		if(r==len+1)break;
	}
	return tot;
}
void dfs(int mid,int last)//mid-->放了几个 
{
	int i,m[220],j,be=n;bool z;
	if(mid-1>=ans)return;
	if(mid>len*3)return;
	if(!n)
	{
		ans=mid-1;
		return ;
	}
	for(i=1;i<=len;i++)m[i]=co[i];
	for(i=last;i<=len;i++)//枚举这个球加在第i个球的前面 
	{
		if(co[i]!=-1)
		{
			z=false;
			find(i);
			if(tot>=2)z=true;
			n-=tot;
			for(j=l+1;j<i;j++)co[j]=-1;
			for(j=r-1;j>=i;j--)co[j]=-1;
			while(n)
			{
				find(i);
				if(tot>=3)
				{
					n-=tot;
					for(j=l+1;j<i;j++)
						co[j]=-1;
					for(j=r-1;j>=i;j--)
						co[j]=-1;
				}
				else break;
			}
			if(z)dfs(mid+1,i+1);
			else dfs(mid+2,i+1);
			n=be;
			for(j=1;j<=len;j++)co[j]=m[j];
		}
	}
}
int main()
{
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	int i;	
	cin>>c;
	len=strlen(c);n=len;
	for(i=0;i<len;i++)co[i+1]=c[i]-'0';
	dfs(1,1);
	printf("%lld",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
