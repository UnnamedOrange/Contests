#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<algorithm>
#define rint register int
using namespace std;
#define MAXN 100005
char a[MAXN+1];
int main() 
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	rint len,tot1=0,tot2=0;
	//scanf("%s",&a);
	gets(a);
	len = strlen(a);
	rint pos1 = len-1;
	rint pos2 = 0;
	while(a[pos1] == 49)//���ܲ�д����49 
		pos1--;//�ҳ���һ������1��λ�á����Ӻ��濪ʼ�� 
	while(a[pos2] == '0')
		pos2++;//�ҳ���һ������0��λ�á�����ǰ�濪ʼ��
	for(rint i=pos1;i>=pos2;i--)
	{
		if(a[i] == 49)//1
			tot1++;
		else
			tot2++;
	}
	int ans = min(tot1,tot2);
	printf("%d",ans);
        return 0; 
}
