#include<bits/stdc++.h>
using namespace std;
char a[10000],tem[10000];
int ans=10000,n=1;
int search(int step,int len)
{
	if(len==1)
	{
		ans=min(ans,step+2);
		return 0;
	}
	int tem3=len;
	for(int i=1;i<=tem3-1;i++)
	{
		if(a[i]=='0'||a[i+1]=='0')
		{
			int p=i,q=i+1,f=0,yes=0,v=0;
			char ch='0';
			while(q<len+1&&p>0)
			{
				while(p>=1&&a[p]==ch)p--;
				while(q<=len&&a[q]==ch)q++;
				if(!f)
				{if(q-p<3)break;}
				else if(q-p-v<4)break;
				yes++;
				v=q-p-1;
				f=1;
				if(q<=len)ch=a[q];
				else ch=a[p];
				if(v==len)
				{
					ans=min(step+1,ans);
					return 0;
				}
			}
			for(int k=1;k<=tem3;k++)tem[k]=a[k],a[k]='\0';
			if(!yes)
			{
				for(int k=1;k<=tem3;k++)
				{
					a[k]=tem[k];
					if(k==i)a[++k]='0';
				}
				len+=1;
			}
			else
			{
				len=0;
				for(int k=1;k<=p;k++)a[k]=tem[k],len++;
				for(int j=q,k=p+1;j<=tem3;k++,j++)a[k]=tem[j],len++;
			}
			if(len==1)ans=min(step+3,ans);
			else if(step<ans)search(step+1,len);
			for(int k=1;k<=tem3;k++)a[k]=tem[k],tem[k]='\0';
			len=tem3;
		}
		if(a[i]=='1'||a[i+1]=='1')
		{
			int p=i,q=i+1,f=0,yes=0,v=0;
			char ch='1';
			while(q<len+1&&p>0)
			{
				
				while(p>=1&&a[p]==ch)p--;
				while(q<=len&&a[q]==ch)q++;
				if(!f){if(q-p<3)break;}
				else if(q-p-v<4)break;
				yes++;
				v=q-p-1;
				f=1;
				if(q<=len)ch=a[q];
				else ch=a[p];
				if(v==len)
				{
					ans=min(step+1,ans);
					return 0;
				}
			}
			int tem2=len;
			for(int k=1;k<=len;k++)tem[k]=a[k],a[k]='\0';
			if(!yes)
			{
				for(int k=1;k<=len;k++)
				{
					a[k]=tem[k];
					if(k==i)a[++k]='1';
				}
				len+=1;
			}
			else
			{
				len=0;
				for(int k=1;k<=p;k++)a[k]=tem[k],len++;
				for(int j=q,k=p+1;j<=tem2;k++,j++)a[k]=tem[j],len++;
			}
			if(len==1)ans=min(step+3,ans);
			else if(step<ans)search(step+1,len);
			for(int k=1;k<=tem3;k++)a[k]=tem[k];
			len=tem3;
		}
	}
}
int main()
{
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	while(cin>>a[n])n++;
	search(0,n-1);
	cout<<ans<<endl;
	return 0;
}
