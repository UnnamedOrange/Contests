#include<cstdio>
using namespace std;
int n,m,a[1000005],k=1,j;
inline int read(){//���� 
	char c;
	while(c<'0'||c>'9')	c=getchar();//�Ե���Ҫ�� 
	while(c>='0'&&c<='9') {a[k++]=c-'0';	c=getchar();}
	k=1;}//��ԭ  	
inline void write()//���
{
	for(int i=1;i<=n;i++)
		putchar(a[i]+'0');	//��ԭ 
}
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
    while(scanf("%d%d",&n,&m)!=EOF)//д==1ֻ�᷵��һ������ 
    {
    	read();
    	for(int i=1;i<=m;i++)
    	{
    		for(j=1;j<=n;j++)
    			if(a[j]==2&&a[j+1]==3)	
					break;
			if(j&1)	a[j+1]=2;
			else	a[j]=3;
		}
		write();putchar('\n');
	}
	return 0;
}
