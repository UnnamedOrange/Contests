#include<bits/stdc++.h>
using namespace std;
int n,m;
int pointx[101000],pointy[101000],ans,addx,addy;double text[101000];
int read()
{
	char c;
	c=getchar();
	while(c>'9'||c<'0')
		c=getchar();
	return c-'0';
}
void search(int l,int r)//���Զ��֣� 
{
	int mid=(l+r)/2;
	if((double)(addy)>=(double)(pointy[mid]-addx*text[mid])&&(double)(addy)<(double)(pointy[mid+1]-addx*text[mid+1]))printf("%d\n",mid);
	if(r>l&&(double)(addy)>=(double)(pointy[mid]-addx*text[mid]))search(mid+1,r);//��Ϊmid������ƫ������ȡ�ұߵ�ʱ��Ҫ��1 
	else if(r>l)search(l,mid);
}
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)pointx[i]=read();//����ԭ���ĵ�
	for(i=1;i<=n;i++)pointy[i]=read();
	sort(pointx+1,pointx+n+1);
	sort(pointy+1,pointy+n+1);
	for(i=1;i<=n;i++)text[i]=double(pointy[i]/pointx[i]);
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{	
		addx=read(),addy=read();//����Ҫ��ѯ�ĵ�
		//scanf("%d%d",&addx,&addy);
		if((double)(addy)>=(double)(pointy[n]-addx*text[n]))printf("%d\n",n);
		else	if((double)(addy)<(double)(pointy[1]-addx*text[1]))printf("0\n");
		else search(1,n-1);//��ans���ұ߲��룬Ҳ����˵Ҫ���ڵ���ansλ�õ��߶Σ�С��ans+1λ�õ��߶� 
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
