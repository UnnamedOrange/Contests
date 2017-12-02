#include<cstdio>
using namespace std;
const int MAXN=1e6+10;
char s[MAXN];
int len;
inline void ans()
{
	for (int i=1;i<=len;i++) printf("%c",s[i]);
	printf("\n");
}
int main()
{
	int k,m;
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	while(scanf("%d%d",&len,&k)!=EOF)
	{
		scanf("%s",s+1);
		
		for(int i=1;i<=len-2;i++)
		{
			if (s[i]=='2' && s[i+1]=='3' && s[i+2]=='3' && i&1){m=i;break;}
			if (s[i]=='2' && s[i+1]=='2' && s[i+2]=='3' && i&1){m=i;break;}
		}
		
		for(int i=1;i<=m-1;i++)
		{
			if (s[i]=='2' && s[i+1]=='3')
			{
				if (i&1) s[i+1]='2';
				else s[i]='3';
				k--;
				if (k==0)break;
			}
		}
		if (k==0 || (k&1)==0) {ans();continue;}
		
		if (s[m+1]=='3') s[m+1]='2';
		else s[m+1]='3';
		ans();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
