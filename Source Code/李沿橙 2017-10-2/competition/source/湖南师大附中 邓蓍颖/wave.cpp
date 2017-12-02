#include<bits/stdc++.h>
using namespace std;
int n,k,high,lowb,now=1,last,ans,s[1000100];/*大于等于k*/
int main()
{
	freopen("wave.in","r",stdin);
	freopen("wave.out","w",stdout);
	int i,a,b; 
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)
		scanf("%d",&s[i]);
	i=1;
	while(i<=n)
	{
		if(now%2)//找奇位 
		{
			while(s[i+1]<s[i])i++;//找到这段最小的 
			last=s[i];//记录最小值 
			i++;
			while(s[i+1]>s[i])i++;//找到这段最大的 
			if(s[i]>=last+k)
			{
				ans++;//如果最大最小搭配合法 
		//		last=s[i];
				now=2;
			}
			else i++;
		}
		else//找偶位 
		{
			while(s[i+1]>s[i])i++;//找到这段最大的 
			last=s[i];//记录最大值 
			i++;
			while(s[i+1]<s[i])i++;//找到这段最小的 
			if(last>=s[i]+k)
			{
				ans++;//如果最大最小搭配合法 
				now=1;
			//	last=s[i];
			}
			else i++;//如果不合法，就跳过这一段，直接接下一段 
		}
	}
	printf("%d",ans+1);
	fclose(stdin);
	fclose(stdout);	
	return 0;
}

