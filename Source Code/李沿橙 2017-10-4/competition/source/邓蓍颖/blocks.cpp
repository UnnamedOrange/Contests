#include<bits/stdc++.h>
using namespace std;
struct abc{
	int tot,date;
};
int n,m,s[1000000],ans,k,all;abc p,maxn;//tot��ͳ�Ƴ��ȣ�ans��¼��󳤶ȣ�maxn��¼��ǰ��ֵ,
/*�����һ������£������Ӧ�Զ����˷Ų��µ���������������ֵ�ܲ��ܳ���tot�������ԣ���˵������ÿ�ζ�һ����ÿ����1��
һֱ������Ϊֹ����Ȼ�Ϳ�������û�дﵽn�����û�дﵽn����ôҲ���Էŵ������ĸ��������ﵽ��n��
�ֳ�����tot���ͱ�����һ�����ӳ�����Ŷ���Ķ���*/
/*������ֱ��̰*/
/*������������������2����������¼�����Լ�Ŀǰ�ۼӣ�
������û��С����Ӧ�е�ֵ�ͼ��룬��������¼���(�������̰���Ǵ�ģ�)*/
int read()
{
	char c;
	c=getchar();
	while(c>'9'||c<'0')c=getchar();
	return c-'0'; 
}
void kkk()
{
	int i,j;abc o;
	maxn.date=0,ans=0,maxn.tot=0,p.date=0,p.tot=0;
	for(i=1;i<=n;i++)
	{
		p.date+=s[i];
		p.tot++;
		if(p.date+maxn.date>=(maxn.tot+p.tot)*k)
		{
			maxn.date+=p.date;
			maxn.tot+=p.tot;
			p.tot=0,p.date=0;
		} 
		else
		{
			j=i+1;
			o.date=0,o.tot=0;
			while(j<=n&&s[j]+o.date>=(o.tot+1)*k)
			{
				o.date+=s[j],o.tot++;
				j++;
			}
			if((o.date-o.tot*k)+(maxn.date-maxn.tot*k)+s[i]>=k)
			{
				maxn.date+=o.date+s[i],maxn.tot+=o.tot+1;
				i=j;
			}
			else
			{
				if(maxn.tot>ans)ans=maxn.tot;
				maxn.tot=0;
				maxn.date=0;
				p.tot=0;
				p.date=0;
			}
		}
	}
	if(maxn.tot>ans)ans=maxn.tot;
	printf("%d ",ans);
}
int main()
{
	freopen("blocks.in","r",stdin);
	freopen("blocks.out","w",stdout);
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&s[i]);
	for(i=1;i<=m;i++)
	{
		scanf("%d",&k);
		kkk();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
