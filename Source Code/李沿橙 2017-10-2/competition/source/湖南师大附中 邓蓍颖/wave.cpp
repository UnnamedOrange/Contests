#include<bits/stdc++.h>
using namespace std;
int n,k,high,lowb,now=1,last,ans,s[1000100];/*���ڵ���k*/
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
		if(now%2)//����λ 
		{
			while(s[i+1]<s[i])i++;//�ҵ������С�� 
			last=s[i];//��¼��Сֵ 
			i++;
			while(s[i+1]>s[i])i++;//�ҵ�������� 
			if(s[i]>=last+k)
			{
				ans++;//��������С����Ϸ� 
		//		last=s[i];
				now=2;
			}
			else i++;
		}
		else//��żλ 
		{
			while(s[i+1]>s[i])i++;//�ҵ�������� 
			last=s[i];//��¼���ֵ 
			i++;
			while(s[i+1]<s[i])i++;//�ҵ������С�� 
			if(last>=s[i]+k)
			{
				ans++;//��������С����Ϸ� 
				now=1;
			//	last=s[i];
			}
			else i++;//������Ϸ�����������һ�Σ�ֱ�ӽ���һ�� 
		}
	}
	printf("%d",ans+1);
	fclose(stdin);
	fclose(stdout);	
	return 0;
}

