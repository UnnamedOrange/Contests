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
	while(a[pos1] == 49)//不能不写等于49 
		pos1--;//找出第一个不是1的位置——从后面开始找 
	while(a[pos2] == '0')
		pos2++;//找出第一个不是0的位置——从前面开始找
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
